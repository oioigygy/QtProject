#include "peoplemanage.h"
#include "ui_peoplemanage.h"

PeopleManage::PeopleManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeopleManage)
{
    ui->setupUi(this);
}

PeopleManage::~PeopleManage()
{
    delete ui;
}
