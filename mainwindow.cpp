#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "QSql"

enum stackedWidget_indcex{
    homepage =0,
    equip,
    people,
    task,
    line
};

MainWindow::MainWindow(QString username,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),username(username)
{
    ui->setupUi(this);
    setWindowTitle("  矿用智能巡检系统  " + username);
    ui->splitter->setStretchFactor(1,5);

    baseinfo = new BaseInfo();
    equipment = new Equipment();
    peoplemanage = new PeopleManage();
    taskmanage = new TaskManage();
    linemanage = new LineManage();

    ui->stackedWidget->addWidget(baseinfo);
     ui->stackedWidget->addWidget(equipment);
    ui->stackedWidget->addWidget(peoplemanage);
    ui->stackedWidget->addWidget(taskmanage);
    ui->stackedWidget->addWidget(linemanage);
    QObject::connect(ui->pb_homepage,&QPushButton::clicked,this,&MainWindow::pb_homepagebtn_clicked);
     QObject::connect(ui->pb_equipment,&QPushButton::clicked,this,&MainWindow::pb_equipmentbtn_clicked);
    QObject::connect(ui->pb_people,&QPushButton::clicked,this,&MainWindow::pb_peoplebtn_clicked);
    QObject::connect(ui->pb_task,&QPushButton::clicked,this,&MainWindow::pb_taskbtn_clicked);
    QObject::connect(ui->pb_line,&QPushButton::clicked,this,&MainWindow::pb_linebtn_clicked);
    TitleBarShow titleshow;
    titleshow.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pb_homepagebtn_clicked(){
        ui->stackedWidget->setCurrentIndex(homepage);
        baseinfo->inittablelist();
}
void MainWindow::pb_equipmentbtn_clicked(){
        ui->stackedWidget->setCurrentIndex(equip);
}
void MainWindow::pb_peoplebtn_clicked(){
        ui->stackedWidget->setCurrentIndex(people);
}
void MainWindow::pb_taskbtn_clicked(){
        ui->stackedWidget->setCurrentIndex(task);
}

void MainWindow::pb_linebtn_clicked(){
        ui->stackedWidget->setCurrentIndex(line);
}

