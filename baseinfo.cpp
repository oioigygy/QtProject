#include "baseinfo.h"
#include "ui_baseinfo.h"
#include "dashboard.h"

BaseInfo::BaseInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseInfo)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("xitong");
    query = new QSqlQuery(db);
    if(!db.open())
    {
        QMessageBox::critical(0, QObject::tr("打开数据库失败！"), db.lastError().text());
    }
    inittablelist();
    ui->stackedWidget->setCurrentIndex(0);

}

BaseInfo::~BaseInfo()
{
    delete ui;
}



void BaseInfo::inittablelist(){
    list_model = new QStandardItemModel(this);
    query->prepare("SELECT * FROM equipment");
    query->exec();
    while(query->next()){
        QString value = query->value("e_name").toString();
        QString id = query->value("e_id").toString();

        item = new QStandardItem(value);
        list_model->appendRow(item);
        item->setToolTip("id：" + id);
        DashBoard *dashboard = new DashBoard(id);
        ui->stackedWidget->addWidget(dashboard);
    }
    ui->listView->setModel(list_model);
    connect(ui->listView,&QListView::clicked,this,[=](){
        page_change(ui->listView->currentIndex());
        qDebug() << "当前index为" << ui->listView->currentIndex().row();

    });
}
void BaseInfo::page_change(QModelIndex page_index){
        ui->stackedWidget->setCurrentIndex(page_index.row());
}






