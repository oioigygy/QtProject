#include "taskmanage.h"
#include "ui_taskmanage.h"

TaskManage::TaskManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManage)
{
    ui->setupUi(this);
}

TaskManage::~TaskManage()
{
    delete ui;
}
