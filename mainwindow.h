#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "titlebarshow.h"
#include "baseinfo.h"
#include "taskmanage.h"
#include "peoplemanage.h"
#include "linemanage.h"
#include "equipment.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString username,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
     QString username;
     BaseInfo *baseinfo;
     Equipment *equipment;
     TaskManage *taskmanage;
     PeopleManage *peoplemanage;
     LineManage *linemanage;



 private slots:
     void pb_homepagebtn_clicked();
     void pb_equipmentbtn_clicked();
     void pb_taskbtn_clicked();
     void pb_peoplebtn_clicked();
     void pb_linebtn_clicked();
};
#endif // MAINWINDOW_H
