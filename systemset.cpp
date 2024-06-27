#include "systemset.h"
#include "ui_systemset.h"

SystemSet::SystemSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSet)
{
    ui->setupUi(this);
}

SystemSet::~SystemSet()
{
    delete ui;
}
