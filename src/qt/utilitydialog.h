// copyright (c) 2011-2014 the dzcoin core developers
// distributed under the mit software license, see the accompanying
// file copying or http://www.opensource.org/licenses/mit-license.php.

#ifndef dzcoin_qt_utilitydialog_h
#define dzcoin_qt_utilitydialog_h

#include <qdialog>
#include <qobject>

class dzcoingui;
class clientmodel;

namespace ui {
    class helpmessagedialog;
}

/** "help message" dialog box */
class helpmessagedialog : public qdialog
{
    q_object

public:
    explicit helpmessagedialog(qwidget *parent, bool about);
    ~helpmessagedialog();

    void printtoconsole();
    void showorprint();

private:
    ui::helpmessagedialog *ui;
    qstring text;

private slots:
    void on_okbutton_accepted();
};


/** "shutdown" window */
class shutdownwindow : public qwidget
{
    q_object

public:
    shutdownwindow(qwidget *parent=0, qt::windowflags f=0);
    static void showshutdownwindow(dzcoingui *window);

protected:
    void closeevent(qcloseevent *event);
};

#endif // dzcoin_qt_utilitydialog_h


