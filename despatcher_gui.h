#ifndef DESPATCHER_GUI_H
#define DESPATCHER_GUI_H

#include <QMainWindow>
#include <QLabel>
#include <algorithm>
#include <string.h>
#include <unistd.h>

extern "C"
{
#include <peiskernel/peiskernel.h>
#include <peiskernel/peiskernel_mt.h>
}

namespace Ui {
class DespatcherGUI;
}

class DespatcherGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DespatcherGUI(QWidget *parent = 0);
    ~DespatcherGUI();

protected slots:
    void postMoveTo();
    void postAcquire();
    void postDock();
    void postLook();
    void postHandover();
    void postPickUp();

private:
	
    Ui::DespatcherGUI *ui;

    void genericStateCheck(std::string tuple_data, std::string action_name, QLabel* label_to_change);
    void postAction(std::string action_name, std::string params);

    static void acquireStateCallback(PeisTuple* tuple, void* _this_);
    static void pickUpStateCallback(PeisTuple* tuple, void* _this_);
    static void moveToStateCallback(PeisTuple* tuple, void* _this_);
    static void dockStateCallback(PeisTuple* tuple, void* _this_);
    static void lookStateCallback(PeisTuple* tuple, void* _this_);
    static void handoverStateCallback(PeisTuple* tuple, void* _this_);
    static void resultCallback(PeisTuple* tuple, void* _this_);
};

#endif // DESPATCHER_GUI_H
