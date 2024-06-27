#include "systemlog.h"
#include "ui_systemlog.h"

SystemLog::SystemLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemLog)
{
    ui->setupUi(this);
}

SystemLog::~SystemLog()
{
    delete ui;
}
