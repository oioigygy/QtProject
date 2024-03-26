#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include "database_manger.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QSqlDatabase db;
//    db = QSqlDatabase::addDatabase("QMYSQL","xitong");
//    db.setDatabaseName("name");
//    db.setUserName("root");
//    db.setPassword("gy184340");
//    bool ok = db.open();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
//        db.setHostName("127.0.0.1");
//        //db.setPort(3306);
//        db.setDatabaseName("name");
//        db.setUserName("root");
//        db.setPassword("gy184340");
//        bool ok = db.open();
//        if (ok){
//            QMessageBox::information(this,"infor", "success");
//        }
//        else {
//            QMessageBox::information(this, "infor", "open failed");
//            qDebug()<<"error open database because"<<db.lastError().text();
//        }


//    if(!ok)
//    {
//        QMessageBox::critical(0, QObject::tr("连接数据库失败！"), db.lastError().text());
//        return 1;
//    }
//    else
//    {
//        qDebug()<<QObject::tr("连接到数据库。"); // 只有在debug模式下才会执行,与cout类似
//    }

//    qApp->setWindowIcon(QIcon(":/images/windowIcon.png"));
//    MainWindow w;
//    w.show();
    Database_Manger d_m;
    Login login;
    login.show();

    return a.exec();
}
