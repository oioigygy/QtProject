#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include  <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPushButton>
#include <QWebSocket>
#include <QtWebEngineWidgets>
#include <QtCharts>           // 引入所有QtCharts绘制的头文件，也可以单独引入某一个头文件
#include<QStandardItemModel>
#include <QLabel>

using namespace QtCharts;     // 使用unsing引入命名空间
QT_CHARTS_USE_NAMESPACE       // 使用内置宏引入命名空间

class DashBoard : public QWidget
{
public:
    DashBoard(QString e_id);

private:
    QSqlDatabase db;
    QSqlQuery *query;
    void initform(QString e_id);
    QList<QWebEngineView *> webViews;
    QWebSocket *webSocket;
    float message_recieve;
    QString sensor_type;
    QString getunit(QString type);
    QLabel empty_sensor;
    DashBoard *dashboard;
};

#endif // DASHBOARD_H
