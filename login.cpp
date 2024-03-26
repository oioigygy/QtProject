#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("xitong");
    query = new QSqlQuery(db);
    setWindowTitle("矿用智能巡检系统");
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

        //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->toolpb_password->setCursor(Qt::PointingHandCursor);
    connect(ui->toolpb_password,&QToolButton::clicked,this,[=](){
        ui->password->setEchoMode(QLineEdit::Normal);
    });
    //updata_user();
    connect(ui->pushButton_enter,&QPushButton::clicked,this,&Login::click_pushbuttor_enter);

}

Login::~Login()
{
    delete ui;
}




void Login::click_pushbuttor_enter(){
    query->clear();
    current_username = ui->username->text();
    current_password = ui->password->text();
    if(current_username == ""){
        QMessageBox::warning(this,"","用户名不能为空！");
    }else if(current_password == ""){
        QMessageBox::warning(this,"","密码不能为空！");
    }else{
        query->exec(QString("SELECT * FROM login WHERE username = '%1' and password = '%2' ").arg(current_username).arg(current_password));
        if(query->next()){
            MainWindow *mainwindow = new MainWindow(ui->username->text(),this);
            mainwindow->show();
            hide();
        }else{
            QMessageBox::warning(this,"","用户名或密码错误！");
        }

    }



}
void Login::mousePressEvent(QMouseEvent *e){

        if(e->button() == Qt::LeftButton)
        {
            //求坐标差值
            //当前点击坐标-窗口左上角坐标
            p = e->globalPos() - this->frameGeometry().topLeft();
        }
    }

void Login::mouseMoveEvent(QMouseEvent *e){

        if(e->buttons() & Qt::LeftButton)
        {
            //移到左上角
            move(e->globalPos() - p);
        }

    }



void Login::on_toolButton_clicked()
{
    showMinimized();
}

void Login::on_toolButton_2_clicked()
{
    close();
}



