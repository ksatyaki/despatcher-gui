#ifndef DESPATCHER_GUI_H
#define DESPATCHER_GUI_H

#include <QMainWindow>

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
};

#endif // DESPATCHER_GUI_H
