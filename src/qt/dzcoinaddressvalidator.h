// copyright (c) 2011-2014 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_qt_dzcoinaddressvalidator_h
#define dzcoin_qt_dzcoinaddressvalidator_h

#include <qvalidator>

/** base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class dzcoinaddressentryvalidator : public qvalidator
{
    q_object

public:
    explicit dzcoinaddressentryvalidator(qobject *parent);

    state validate(qstring &input, int &pos) const;
};

/** dzcoin address widget validator, checks for a valid dzcoin address.
 */
class dzcoinaddresscheckvalidator : public qvalidator
{
    q_object

public:
    explicit dzcoinaddresscheckvalidator(qobject *parent);

    state validate(qstring &input, int &pos) const;
};

#endif // dzcoin_qt_dzcoinaddressvalidator_h


