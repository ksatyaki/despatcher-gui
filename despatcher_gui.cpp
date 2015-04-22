#include "despatcher_gui.h"
#include "ui_despatcher_gui.h"

DespatcherGUI::DespatcherGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DespatcherGUI)
{
    ui->setupUi(this);

    int argn = 0;
    char* args[] = { "despatcher-gui" };
    peiskmt_initialize(&argn, args);

	peiskmt_subscribe(999, "out.doro.pickup.state");
	peiskmt_subscribe(999, "out.doro.acquire.state");
	peiskmt_subscribe(999, "out.doro.moveto.state");
	peiskmt_subscribe(999, "out.doro.look.state");
	peiskmt_subscribe(999, "out.doro.dock.state");
	peiskmt_subscribe(999, "out.doro.handover.state");

    peiskmt_registerTupleCallback(999, "out.doro.pickup.state", this, &DespatcherGUI::callbackFunction);
    peiskmt_registerTupleCallback(999, "out.doro.moveto.state", this, &DespatcherGUI::callbackFunction);
    peiskmt_registerTupleCallback(999, "out.doro.acquire.state", this, &DespatcherGUI::callbackFunction);
    peiskmt_registerTupleCallback(999, "out.doro.dock.state", this, &DespatcherGUI::callbackFunction);
    peiskmt_registerTupleCallback(999, "out.doro.look.state", this, &DespatcherGUI::callbackFunction);
    peiskmt_registerTupleCallback(999, "out.doro.handover.state", this, &DespatcherGUI::callbackFunction);


}

void DespatcherGUI::callbackFunction(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    char* action_str = tuple->keys[2];
    QLabel* label_to_change;

    if(strcmp("pickup", action_str) == 0)
    {
        label_to_change = this_ptr->ui->PickUpLabel;
    }
    else if(strcmp(action_str, "acquire") == 0)
    {
        label_to_change = this_ptr->ui->AcquireLabel;
    }
    else if(strcmp(action_str, "moveto") == 0)
    {
        label_to_change = this_ptr->ui->MoveToLabel;
    }
    else if(strcmp(action_str, "dock") == 0)
    {
        label_to_change = this_ptr->ui->DockLabel;
    }
    else if(strcmp(action_str, "look") == 0)
    {
        label_to_change = this_ptr->ui->LookLabel;
    }
    else if(strcmp(action_str, "handover") == 0)
    {
        label_to_change = this_ptr->ui->HandoverLabel;
    }
    else
    {
        printf("Can't find label for %s!\n", action_str);
        return;
    }

    if(strcmp("IDLE", tuple->data) == 0)
    {
        label_to_change->setStyleSheet("QLabel { background-color: yellow; color: black; }");
    }
    else if(strcmp("COMPLETED", tuple->data) == 0)
    {
        label_to_change->setStyleSheet("QLabel { background-color: green; color : black; }");
    }
    else if(strcmp("FAILED", tuple->data) == 0)
    {
        label_to_change->setStyleSheet("QLabel { background-color: red; color : black; }");
    }
    else if(strcmp("RUNNING", tuple->data) == 0)
    {
        label_to_change->setStyleSheet("QLabel { background-color: blue; color : white; }");
    }

    label_to_change->setText(tuple->data);
}

DespatcherGUI::~DespatcherGUI()
{
	peiskmt_shutdown();
    delete ui;
}
