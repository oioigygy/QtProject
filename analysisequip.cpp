#include "analysisequip.h"
#include "ui_analysisequip.h"

AnalysisEquip::AnalysisEquip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalysisEquip)
{
    ui->setupUi(this);
}

AnalysisEquip::~AnalysisEquip()
{
    delete ui;
}
