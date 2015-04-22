#include "despatcher_gui.h"
#include "ui_despatcher_gui.h"

DespatcherGUI::DespatcherGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DespatcherGUI)
{
    ui->setupUi(this);
}

DespatcherGUI::~DespatcherGUI()
{
    delete ui;
}
