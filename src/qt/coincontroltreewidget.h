// copyright (c) 2011-2013 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_qt_coincontroltreewidget_h
#define dzcoin_qt_coincontroltreewidget_h

#include <qkeyevent>
#include <qtreewidget>

class coincontroltreewidget : public qtreewidget
{
    q_object

public:
    explicit coincontroltreewidget(qwidget *parent = 0);

protected:
    virtual void keypressevent(qkeyevent *event);
};

#endif // dzcoin_qt_coincontroltreewidget_h


