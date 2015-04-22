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
    peiskmt_subscribe(999, "out.doro.acquire.result");

    peiskmt_registerTupleCallback(999, "out.doro.pickup.state", this, &DespatcherGUI::pickUpStateCallback);
    peiskmt_registerTupleCallback(999, "out.doro.moveto.state", this, &DespatcherGUI::moveToStateCallback);
    peiskmt_registerTupleCallback(999, "out.doro.acquire.state", this, &DespatcherGUI::acquireStateCallback);
    peiskmt_registerTupleCallback(999, "out.doro.dock.state", this, &DespatcherGUI::dockStateCallback);
    peiskmt_registerTupleCallback(999, "out.doro.look.state", this, &DespatcherGUI::lookStateCallback);
    peiskmt_registerTupleCallback(999, "out.doro.handover.state", this, &DespatcherGUI::handoverStateCallback);

    peiskmt_registerTupleCallback(999, "out.doro.acquire.result", this, &DespatcherGUI::resultCallback);


    // Connections
    connect(ui->QuitPushButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->AcquireButton, SIGNAL(clicked()), this, SLOT(postAcquire()));
    connect(ui->DockButton, SIGNAL(clicked()), this, SLOT(postDock()));
    connect(ui->LookButton, SIGNAL(clicked()), this, SLOT(postLook()));
    connect(ui->PickUpButton, SIGNAL(clicked()), this, SLOT(postPickUp()));
    connect(ui->HandoverButton, SIGNAL(clicked()), this, SLOT(postHandover()));
    connect(ui->MoveToButton, SIGNAL(clicked()), this, SLOT(postMoveTo()));

}

void DespatcherGUI::postMoveTo()
{
    postAction("moveto", ui->MoveToLineEdit->text().toStdString());
}

void DespatcherGUI::postAcquire()
{
    postAction("acquire", ui->AcquireLineEdit->text().toStdString());
}

void DespatcherGUI::postPickUp()
{
    postAction("pickup", ui->PickUpLineEdit->text().toStdString());
}

void DespatcherGUI::postHandover()
{
    postAction("handover", ui->HandoverLineEdit->text().toStdString());
}

void DespatcherGUI::postDock()
{
    postAction("dock", ui->DockLineEdit->text().toStdString());
}

void DespatcherGUI::postLook()
{
    postAction("look", ui->LookLineEdit->text().toStdString());
}

void DespatcherGUI::postAction(std::string action_name, std::string params)
{
    std::string my_command = "out.doro." + action_name + ".command";
    std::string my_params = "out.doro." + action_name + ".parameters";

    peiskmt_setStringTuple(my_command.c_str() , "ON");
    peiskmt_setStringTuple(my_params.c_str(), params.c_str());

    peiskmt_setMetaTuple(999, std::string("in.doro." + action_name + ".command").c_str(), peiskmt_peisid(), my_command.c_str());
    peiskmt_setMetaTuple(999, std::string("in.doro." + action_name + ".parameters").c_str(), peiskmt_peisid(), my_params.c_str());
}

/**
 * @brief DespatcherGUI::resultCallback Callback happens when acquire's result changes.
 * @param tuple The new tuple.
 * @param _this_ The 'this' pointer passed in.
 */
void DespatcherGUI::resultCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->ui->AcquireResultLabel->setText(tuple->data);
}

void DespatcherGUI::pickUpStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "pickup", this_ptr->ui->PickUpLabel);

    this_ptr->ui->PickUpLabel->setText(tuple->data);
}

void DespatcherGUI::handoverStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "handover", this_ptr->ui->HandoverLabel);

    this_ptr->ui->HandoverLabel->setText(tuple->data);
}

void DespatcherGUI::moveToStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "moveto", this_ptr->ui->MoveToLabel);

    this_ptr->ui->MoveToLabel->setText(tuple->data);
}

void DespatcherGUI::dockStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "dock", this_ptr->ui->DockLabel);

    this_ptr->ui->DockLabel->setText(tuple->data);
}

void DespatcherGUI::lookStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "look", this_ptr->ui->LookLabel);

    this_ptr->ui->LookLabel->setText(tuple->data);
}

void DespatcherGUI::acquireStateCallback(PeisTuple* tuple, void* _this_)
{
    DespatcherGUI* this_ptr = static_cast<DespatcherGUI*>(_this_);

    this_ptr->genericStateCheck(tuple->data, "acquire", this_ptr->ui->AcquireLabel);

    this_ptr->ui->AcquireLabel->setText(tuple->data);
}

void DespatcherGUI::genericStateCheck(std::string tuple_data, std::string action_name, QLabel* label_to_change)
{

    if(tuple_data.compare("COMPLETED") == 0)
    {
        peisk_setMetaTuple(999, std::string("in.doro." + action_name + ".command").c_str(), -1, "NULL");
        peisk_setMetaTuple(999, std::string("in.doro." + action_name + ".parameters").c_str(), -1, "NULL");
        peisk_setRemoteStringTuple(999, std::string("out.doro." + action_name + ".state").c_str(), "IDLE");
    }
    else if(tuple_data.compare("FAILED") == 0)
    {
        peisk_setMetaTuple(999, std::string("in.doro." + action_name + ".command").c_str(), -1, "NULL");
        peisk_setMetaTuple(999, std::string("in.doro." + action_name + ".parameters").c_str(), -1, "NULL");
        peisk_setRemoteStringTuple(999, std::string("out.doro." + action_name + ".state").c_str(), "IDLE");
    }
}

DespatcherGUI::~DespatcherGUI()
{
	peiskmt_shutdown();
    delete ui;
}
