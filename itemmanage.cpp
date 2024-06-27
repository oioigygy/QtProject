#include "linemanage.h"
#include "ui_linemanage.h"

LineManage::LineManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineManage)
{
    ui->setupUi(this);
}

LineManage::~LineManage()
{
    delete ui;
}
