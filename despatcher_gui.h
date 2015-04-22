#ifndef DESPATCHER_GUI_H
#define DESPATCHER_GUI_H

#include <QMainWindow>
#include <algorithm>
#include <string.h>
#include <unistd.h>

extern "C"
{
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

private:
	
    Ui::DespatcherGUI *ui;

    static void callbackFunction(PeisTuple* tuple, void* user_data);
};

#endif // DESPATCHER_GUI_H
