#include "equipment.h"
#include "ui_equipment.h"

enum {
    statu_change =0,
    statu_submit
};

Equipment::Equipment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipment)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("xitong");
    query = new QSqlQuery(db);
    if(!db.open())
    {
        QMessageBox::critical(0, QObject::tr("打开数据库失败！"), db.lastError().text());
    }

        init_select_edit();
        init_tableview_e();


}

Equipment::~Equipment()
{
    delete ui;
}



void Equipment::init_select_edit(){
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, [=](){
            on_pb_select_clicked();
        });
    ui->lineEdit->setPlaceholderText("请输入查询内容");
    QStringList list;
        //list内容根据需求自行添加
        list << "提升机" << "" << "压风机" << "井筒" ;

    completer = new QCompleter(list,this);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit->setCompleter(completer);
}
void Equipment::init_tableview_e(){
    //显示设备列表
    model = new QSqlTableModel(this,db);
    model->setTable("equipment");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView_equipment->setModel(model);
    ui->tableView_equipment->setContextMenuPolicy(Qt::CustomContextMenu);

    //QPoint p = QCursor::pos(); //当前鼠标位置
    connect(ui->tableView_equipment,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(CreateMenu(QPoint)));
    QStringList columnlist;
    model->setHeaderData(0, Qt::Horizontal, "设备名称");
    model->setHeaderData(1, Qt::Horizontal, "设备id");
    model->setHeaderData(2, Qt::Horizontal, "安装位置");
    model->setHeaderData(3, Qt::Horizontal, "设备型号");
    model->setHeaderData(4, Qt::Horizontal, "生产厂家");
    model->setHeaderData(5, Qt::Horizontal, "出厂日期");
     model->setHeaderData(6, Qt::Horizontal, "备注");
}

void Equipment::on_tableView_equipment_clicked(const QModelIndex &index)
{
        qDebug() << "选中数值为：" << model->data(model->index(index.row(),1)).toInt();
        int e_id_select = model->data(model->index(index.row(),1)).toInt();
        mode= new QSqlTableModel(this);
        mode->setQuery(QString("SELECT e_c_name FROM child_equipment WHERE e_id = '%1' ").arg(e_id_select),db);
        qDebug() << mode->lastError();
        ui->tableView_child->setModel(mode);
        mode->setHeaderData(0, Qt::Horizontal, "子部件名称");
//        if (!mode-)) {
//            qDebug() << "Query Error: " << query.lastError().text();
//        }

}

void Equipment::on_pb_add_clicked()
{
    ui->pb_change->setDisabled(true);
    ui->pb_delete->setDisabled(true);
    ui->pb_select->setDisabled(true);
    ui->pb_add->setEnabled(false);

    pb_enter = new QPushButton();
    pb_cancel = new QPushButton();
    pb_enter->setText("确定");
    pb_cancel->setText("取消");

    ui->horizontalLayout_pb->addWidget(pb_enter);
     ui->horizontalLayout_pb->addWidget(pb_cancel);

     int rowCount = model-> rowCount();
    qDebug() << "添加第" << rowCount << "行";
    model->insertRows(rowCount,1);
    ui->tableView_equipment->setEditTriggers(QTableView::DoubleClicked);

    connect(pb_enter,&QPushButton::clicked,this,&Equipment::pb_enter_clicked);
    connect(pb_cancel,&QPushButton::clicked,this,&Equipment::pb_cancel_clicked);


    //model->setData()
}

void Equipment::CreateMenu(QPoint pos)
{
    qDebug() << "开始创建菜单" ;
    QModelIndex index = ui->tableView_equipment->indexAt(pos);
    tableviewMenu = new QMenu(ui->tableView_equipment);
    if(index.isValid()){
        on_tableView_equipment_clicked(index);
        add_c_e = new QAction("添加子部件",ui->tableView_equipment);
        add_status = new QAction("添加传感器",ui->tableView_equipment);
        qDebug() << "index.row=" << index.row();
        add_c_e->setData(index.row());
        tableviewMenu->addAction(add_c_e);

        tableviewMenu->addSeparator(); // 添加分割线}
        tableviewMenu->addAction(add_status);
        // 连接信号和槽，使用新的连接语法
        connect(add_c_e, &QAction::triggered, this, [=](){
            SlotMenuClicked(index);
        });

        connect(add_status, &QAction::triggered, this, [=](){
            add_status_Clicked(index);
        });
        tableviewMenu->exec(QCursor::pos());  // 菜单显示到鼠标的位置
    }else{
        qDebug() << "index出错" ;
    }

        QList<QAction*> list = tableviewMenu->actions();  //清空内存
        foreach(QAction * pAction, list) delete pAction;
        delete tableviewMenu;
}

void Equipment::SlotMenuClicked(QModelIndex index)
{

    ui->pb_change->setDisabled(true);
    ui->pb_delete->setDisabled(true);
    ui->pb_select->setDisabled(true);
    ui->pb_add->setEnabled(false);

      bool btn_ok = false;
     QString e_c_name_add = QInputDialog::getText(this,
                                                                                "添加子部件",
                                                                                "请输入添加的子部件：",
                                                                                QLineEdit::Normal,
                                                                                "",
                                                                                &btn_ok);
    if(btn_ok && !e_c_name_add.isEmpty()){
        qDebug() << "index.row和ecname分别是:"  << index.row() << e_c_name_add;
        qDebug() << "id为" << model->data(model->index(index.row(),1)).toInt();


        query->exec(QString("INSERT INTO CHILD_EQUIPMENT VALUE('%1','%2')").arg(e_c_name_add).arg(model->data(model->index(index.row(),1)).toInt()));
        qDebug() << query->lastError();
        on_tableView_equipment_clicked(index);
    }else if(btn_ok && e_c_name_add.isEmpty()){
        QMessageBox::warning(this,"错误","不能为空！ " );
    }
    ui->pb_change->setDisabled(false);
    ui->pb_delete->setDisabled(false);
    ui->pb_select->setDisabled(false);
    ui->pb_add->setEnabled(true);
}

void  Equipment::add_status_Clicked(QModelIndex index){
    qDebug() << "添加界面";
        QDialog dialog(this);
        form = new QFormLayout();
        QVBoxLayout *form_button = new QVBoxLayout(&dialog); // 直接传递 QWidget 指针
        dialog.setWindowTitle(QString("添加传感器数据"));


            //表格布局
            QLabel *value_qml = new QLabel("qml地址：");
            QLineEdit *line_qml = new QLineEdit();
            QLabel *value_name = new QLabel("传感器类型：");
            QComboBox *line_name = new QComboBox();
            QStringList list_name;
            list_name << "温度" << "油位" << "倾角" << "加速度" << "CO浓度" << "CO2浓度" << "CH4浓度" << "粉尘浓度" ;
            line_name->addItems(list_name);
            form->addRow(value_qml, line_qml);
            form->addRow(value_name, line_name);
            add_row = new QPushButton();
            add_row->setText("+");
            add_row->setStyleSheet("color:green;");
            add_row->setFixedSize(20,20);
            form->addRow(add_row);
             add_rows_num=1;
            connect(add_row,&QPushButton::clicked,this,[=](){
                if(add_rows_num>=8){
                    QMessageBox::warning(this,"添加超出数量限制！","最多添加八个传感器！");
                    return 0;
                }
                QLabel *value_qml = new QLabel("qml地址：");
                QLineEdit *line_qml = new QLineEdit();
                QLabel *value_name = new QLabel("传感器类型：");
                QComboBox *line_name = new QComboBox();
                QStringList list_name;
                list_name << "温度" << "油位" << "倾角" << "加速度" << "CO浓度" << "CO2浓度" << "CH4浓度" << "粉尘浓度" ;
                line_name->addItems(list_name);
                form->addRow(value_qml, line_qml);
                form->addRow(value_name, line_name);
                form->addRow(add_row); //通过这个可以直接将+移到最后一行
                add_rows_num++;
            });
            //垂直布局

            //连接确定取消按钮
            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal,&dialog);
            connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, [&](){
                qDebug() << "确认按下";

                qDebug() << "当前rowcount为：" << form->rowCount();
                for(int i=0;i<form->rowCount();i+=3){
                    qDebug() << "第" << i ;
                    QLayoutItem *item = form->itemAt(i,QFormLayout::FieldRole);
                    if (!item) {
                        qDebug() <<"选中item出错" ;
                                continue;

                            }
                    QLineEdit *e = (QLineEdit *)item->widget();
                    if(!e){
                        continue;
                    }
                    //比较分辨lineedit和combobox
                    if(strncmp(item->widget()->metaObject()->className(),"QLineEdit",9) ==0){
                        qDebug() << "识别到linedit" ;
                        qDebug() << "当前qml地址为" << e->text();
                        if(e->text() == nullptr){
                            QToolTip::showText(e->mapToGlobal(QPoint(100, 0)), "qml地址不能为空！！");
                            e->setStyleSheet("QLineEdit{border:1px solid red }");
                            haserror = true;
                            break;
                        }else {
                            QRegExp rx("^ws://127\\.0\\.0\\.1:1880/.*$");
                            if(rx.exactMatch(e->text())){
                                haserror = false;
                                e->setStyleSheet("QLineEdit{border:1px solid gray border-radius:1px}");
                                qDebug() << "匹配成功" ;
                            }else{
                                QToolTip::showText(e->mapToGlobal(QPoint(100, 0)), "qml地址无效");
                                haserror = true;
                                e->setStyleSheet("QLineEdit{border:1px solid red }");
                                break;
                                //QMessageBox::warning(this,"qml地址无效","输入的qml地址无效，请仔细检查！")
                            }
                        }
                    }
                }
                if(!haserror){
                    qDebug() << "成功" ;
                    qDebug() << "当前id为" << model->data(model->index(index.row(),1)).toInt();
                    for(int i=0;i<form->rowCount();i++){
                        QLayoutItem *item_new = form->itemAt(i,QFormLayout::FieldRole);
                        QLineEdit *e_new = (QLineEdit *)item_new->widget();
                        i++;  //转到combobox
                        QLayoutItem *item_new_cob = form->itemAt(i,QFormLayout::FieldRole);
                        QComboBox *e_new_cob = (QComboBox *)item_new_cob->widget();
                        qDebug() << "应该插入的堆积页数为： " << index.row();
                        query->exec(QString("INSERT INTO e_qml (e_id ,qml_address,stacked_page,sensor_type) VALUE('%1','%2','%3','%4')")
                                    .arg(model->data(model->index(index.row(),1)).toInt()).arg(e_new->text())
                                    .arg(index.row()).arg(e_new_cob->currentText()));//插入
                        qDebug() << "添加结果：" << query->lastError();
                        i++;
                    }
                    QMessageBox::information(this,"成功！" ,"添加成功！");
                    dialog.accept();
                }
            });


            ;
            connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
            form_button->setDirection(QBoxLayout::TopToBottom);
            form_button->addLayout(form);
            form_button->addWidget(&buttonBox,1);
            dialog.setLayout(form_button);
            dialog.exec();

                // exec才能显示出窗口
}



void Equipment::pb_enter_clicked(){
        qDebug() << "当前计数为" << model->rowCount() ;
         qDebug() << "坐标为" <<model->index(model->rowCount()-1,1) ;
          qDebug() << "data为" << model->data(model->index(model->rowCount()-1,1)) ;

        if((model->data(model->index(model->rowCount()-1,1)).toInt()) == 0){
            qDebug() << "id坐标为" << model->rowCount() ;
            QMessageBox::warning(this,"警告","设备id不能为空！");
            pb_cancel_clicked();
        }else if((model->data(model->index(model->rowCount()-1,0)).toString()) == nullptr){
            QMessageBox::warning(this,"警告","设备名称不能为空！");
            pb_cancel_clicked();
        }
        database_submit(model);
        pb_enter->hide();
        pb_cancel->hide();

        ui->pb_change->setDisabled(false);
        ui->pb_delete->setDisabled(false);
        ui->pb_select->setDisabled(false);
        ui->pb_add->setEnabled(true);
        ui->tableView_equipment->setEditTriggers(QTableView::NoEditTriggers);
}
void Equipment::pb_cancel_clicked(){
    // qDebug() << "删除第" << model->rowCount() << "行" ;
        model->removeRows(model->rowCount()-1,1);
        pb_enter->hide();
        pb_cancel->hide();

        ui->pb_change->setDisabled(false);
        ui->pb_delete->setDisabled(false);
        ui->pb_select->setDisabled(false);
        ui->pb_add->setEnabled(true);
        ui->tableView_equipment->setEditTriggers(QTableView::NoEditTriggers);
}


void Equipment::database_submit(QSqlTableModel *model_d){
        //开启事务
        model_d->database().transaction();
        if (model_d->submitAll())
        {
            //提交事务
            model_d->database().commit();
        }
        else
        {
            //回滚事务
           model_d->database().rollback();
            if (model_d->lastError().isValid()) {
                // 检查错误信息是否为主键重复错误
                qDebug() << "错误代号：" << model_d->lastError().nativeErrorCode();
                if (model_d->lastError().nativeErrorCode() == "1062") { // MySQL 错误代码 1062 表示主键重复错误
                    QMessageBox::warning(this, "警告", "输入的 ID 已经存在！");
                    pb_cancel_clicked();
                } else {
                    // 其他类型的数据库错误
                    qDebug() << "数据库错误:" << query->lastError().text();
                     QMessageBox::warning(this, tr("TableView"), tr("数据库错误: %1").arg(model_d->lastError().text()));
                }
            }

        }

}

void Equipment::on_pb_select_clicked()
{
    ui->pb_change->setDisabled(true);
    ui->pb_delete->setDisabled(true);
    ui->pb_add->setEnabled(false);
    QString name = ui->lineEdit->text();
    qDebug() << "输入名称为" << name;
    if(!(name == nullptr)){
        model->setFilter(QString("e_name = '%1' ").arg(name));
        model->select();
    }

}

void Equipment::on_pb_delete_clicked()
{
    int delete_choose;
       delete_choose= QMessageBox::question(this, tr("删除"),
                                       QString(tr("确认删除该项?")),
                                       QMessageBox::Yes | QMessageBox::No);
       if(delete_choose == QMessageBox::Yes){
           model->removeRow(ui->tableView_equipment->currentIndex().row());
           int e_id_select = model->data(model->index(ui->tableView_equipment->currentIndex().row(),1)).toInt();
           qDebug() << "选中id为" << e_id_select;
           database_submit(model);
           query->exec(QString("DELETE  FROM child_equipment WHERE e_id = '%1' ").arg(e_id_select));
           qDebug() << query->lastError();

       }



    //删除子部件
}

void Equipment::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1 == nullptr){
        init_tableview_e();
        ui->pb_change->setDisabled(false);
        ui->pb_delete->setDisabled(false);
        ui->pb_add->setEnabled(true);
    }
}

void Equipment::on_pb_change_clicked()
{
    qDebug() << "change_status，statu_change" <<change_status << "," <<statu_change;
    if(change_status == statu_change){
        ui->pb_delete->setDisabled(true);
        ui->pb_select->setDisabled(true);
        ui->pb_add->setEnabled(false);
        ui->tableView_equipment->setEditTriggers(QTableView::DoubleClicked);
        ui->pb_change->setText("提交");
        change_status = statu_submit;
        return;
    }
    if(change_status == statu_submit){
        ui->pb_delete->setDisabled(false);
        ui->pb_select->setDisabled(false);
        ui->pb_add->setEnabled(true);
        ui->pb_change->setText("修改");
        ui->pb_change->setEnabled(true);
        ui->tableView_equipment->setEditTriggers(QTableView::NoEditTriggers);
        change_status = statu_change;
        return;
    }
    //

}
