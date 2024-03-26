#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include  <QtSql>
#include <QMessageBox>
#include "mainwindow.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:
   // void updata_user();
private:
    Ui::Login *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QString current_username;
    QString current_password;
    QPoint p;



private slots:
    void click_pushbuttor_enter();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();


protected:

    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动
};



#endif // LOGIN_H
