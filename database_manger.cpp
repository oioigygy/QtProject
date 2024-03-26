#include "database_manger.h"
#include <QApplication>

Database_Manger::Database_Manger()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","xitong");
       // db.setHostName("127.0.0.1");
        //db.setPort(3306);
        db.setDatabaseName("name");//odbc下这里是数据源名称
        db.setUserName("root");
        db.setPassword("gy184340");
        bool ok = db.open();

        if (ok){
            qDebug()<<" database open";
        }
        else {
            QMessageBox::information(this, "infor", "open failed");
            qDebug()<<"error open database because"<<db.lastError().text();
        }
}
