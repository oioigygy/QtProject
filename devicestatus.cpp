#include "devicestatus.h"
#include "ui_devicestatus.h"

DeviceStatus::DeviceStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceStatus)
{
    ui->setupUi(this);
}

DeviceStatus::~DeviceStatus()
{
    delete ui;
}

void init_status(){

}
