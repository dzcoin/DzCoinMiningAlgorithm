// copyright (c) 2011-2013 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_qt_qvaluecombobox_h
#define dzcoin_qt_qvaluecombobox_h

#include <qcombobox>
#include <qvariant>

/* qcombobox that can be used with qdatawidgetmapper to select ordinal values from a model. */
class qvaluecombobox : public qcombobox
{
    q_object

    q_property(qvariant value read value write setvalue notify valuechanged user true)

public:
    explicit qvaluecombobox(qwidget *parent = 0);

    qvariant value() const;
    void setvalue(const qvariant &value);

    /** specify model role to use as ordinal value (defaults to qt::userrole) */
    void setrole(int role);

signals:
    void valuechanged();

private:
    int role;

private slots:
    void handleselectionchanged(int idx);
};

#endif // dzcoin_qt_qvaluecombobox_h


