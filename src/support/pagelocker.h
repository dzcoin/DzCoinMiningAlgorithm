﻿// copyright (c) 2009-2010 satoshi nakamoto
// copyright (c) 2009-2013 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_support_pagelocker_h
#define dzcoin_support_pagelocker_h

#include "support/cleanse.h"

#include <map>

#include <boost/thread/mutex.hpp>
#include <boost/thread/once.hpp>

/**
 * thread-safe class to keep track of locked (ie, non-swappable) memory pages.
 *
 * memory locks do not stack, that is, pages which have been locked several times by calls to mlock()
 * will be unlocked by a single call to munlock(). this can result in keying material ending up in swap when
 * those functions are used naively. this class simulates stacking memory locks by keeping a counter per page.
 *
 * @note by using a map from each page base address to lock count, this class is optimized for
 * small objects that span up to a few pages, mostly smaller than a page. to support large allocations,
 * something like an interval tree would be the preferred data structure.
 */
template <class locker>
class lockedpagemanagerbase
{
public:
    lockedpagemanagerbase(size_t page_size) : page_size(page_size)
    {
        // determine bitmask for extracting page from address
        assert(!(page_size & (page_size - 1))); // size must be power of two
        page_mask = ~(page_size - 1);
    }

    ~lockedpagemanagerbase()
    {
    }


    // for all pages in affected range, increase lock count
    void lockrange(void* p, size_t size)
    {
        boost::mutex::scoped_lock lock(mutex);
        if (!size)
            return;
        const size_t base_addr = reinterpret_cast<size_t>(p);
        const size_t start_page = base_addr & page_mask;
        const size_t end_page = (base_addr + size - 1) & page_mask;
        for (size_t page = start_page; page <= end_page; page += page_size) {
            histogram::iterator it = histogram.find(page);
            if (it == histogram.end()) // newly locked page
            {
                locker.lock(reinterpret_cast<void*>(page), page_size);
                histogram.insert(std::make_pair(page, 1));
            } else // page was already locked; increase counter
            {
                it->second += 1;
            }
        }
    }

    // for all pages in affected range, decrease lock count
    void unlockrange(void* p, size_t size)
    {
        boost::mutex::scoped_lock lock(mutex);
        if (!size)
            return;
        const size_t base_addr = reinterpret_cast<size_t>(p);
        const size_t start_page = base_addr & page_mask;
        const size_t end_page = (base_addr + size - 1) & page_mask;
        for (size_t page = start_page; page <= end_page; page += page_size) {
            histogram::iterator it = histogram.find(page);
            assert(it != histogram.end()); // cannot unlock an area that was not locked
            // decrease counter for page, when it is zero, the page will be unlocked
            it->second -= 1;
            if (it->second == 0) // nothing on the page anymore that keeps it locked
            {
                // unlock page and remove the count from histogram
                locker.unlock(reinterpret_cast<void*>(page), page_size);
                histogram.erase(it);
            }
        }
    }

    // get number of locked pages for diagnostics
    int getlockedpagecount()
    {
        boost::mutex::scoped_lock lock(mutex);
        return histogram.size();
    }

private:
    locker locker;
    boost::mutex mutex;
    size_t page_size, page_mask;
    // map of page base address to lock count
    typedef std::map<size_t, int> histogram;
    histogram histogram;
};


/**
 * os-dependent memory page locking/unlocking.
 * defined as policy class to make stubbing for test possible.
 */
class memorypagelocker
{
public:
    /** lock memory pages.
     * addr and len must be a multiple of the system page size
     */
    bool lock(const void* addr, size_t len);
    /** unlock memory pages.
     * addr and len must be a multiple of the system page size
     */
    bool unlock(const void* addr, size_t len);
};

/**
 * singleton class to keep track of locked (ie, non-swappable) memory pages, for use in
 * std::allocator templates.
 *
 * some implementations of the stl allocate memory in some constructors (i.e., see
 * msvc's vector<t> implementation where it allocates 1 byte of memory in the allocator.)
 * due to the unpredictable order of static initializers, we have to make sure the
 * lockedpagemanager instance exists before any other stl-based objects that use
 * secure_allocator are created. so instead of having lockedpagemanager also be
 * static-initialized, it is created on demand.
 */
class lockedpagemanager : public lockedpagemanagerbase<memorypagelocker>
{
public:
    static lockedpagemanager& instance()
    {
        boost::call_once(lockedpagemanager::createinstance, lockedpagemanager::init_flag);
        return *lockedpagemanager::_instance;
    }

private:
    lockedpagemanager();

    static void createinstance()
    {
        // using a local static instance guarantees that the object is initialized
        // when it's first needed and also deinitialized after all objects that use
        // it are done with it.  i can think of one unlikely scenario where we may
        // have a static deinitialization order/problem, but the check in
        // lockedpagemanagerbase's destructor helps us detect if that ever happens.
        static lockedpagemanager instance;
        lockedpagemanager::_instance = &instance;
    }

    static lockedpagemanager* _instance;
    static boost::once_flag init_flag;
};

//
// functions for directly locking/unlocking memory objects.
// intended for non-dynamically allocated structures.
//
template <typename t>
void lockobject(const t& t)
{
    lockedpagemanager::instance().lockrange((void*)(&t), sizeof(t));
}

template <typename t>
void unlockobject(const t& t)
{
    memory_cleanse((void*)(&t), sizeof(t));
    lockedpagemanager::instance().unlockrange((void*)(&t), sizeof(t));
}

#endif // dzcoin_support_pagelocker_h


