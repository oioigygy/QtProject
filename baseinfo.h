#ifndef BASEINFO_H
#define BASEINFO_H

#include <QWidget>
#include  <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPushButton>
#include <QWebSocket>
#include <QtWebEngineWidgets>
#include <QtCharts>           // 引入所有QtCharts绘制的头文件，也可以单独引入某一个头文件
#include<QStandardItemModel>
#include "dashboard.h"

// 两种引入命名空间方法
using namespace QtCharts;     // 使用unsing引入命名空间
QT_CHARTS_USE_NAMESPACE       // 使用内置宏引入命名空间

namespace Ui {
class BaseInfo;
}

class BaseInfo : public QWidget
{
    Q_OBJECT

public:
    explicit BaseInfo(QWidget *parent = nullptr);
    ~BaseInfo();

public slots:
    void inittablelist();

private:
    Ui::BaseInfo *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    QWebEngineView *m_view = nullptr;
    QList<QWebEngineView *> webViews;
    QStandardItemModel *list_model;
    QStandardItem *item;

private slots:
    void page_change(QModelIndex page_index);
    //void inittablelist();

    //void on_verticalScrollBar_valueChanged(int value);
};

#endif // BASEINFO_H
