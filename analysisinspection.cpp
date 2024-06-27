#include "analysisinspection.h"
#include "ui_analysisinspection.h"

AnalysisInspection::AnalysisInspection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalysisInspection)
{
    ui->setupUi(this);
}

AnalysisInspection::~AnalysisInspection()
{
    delete ui;
}
