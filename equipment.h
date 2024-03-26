#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QWidget>
#include  <QtSql>
#include <QMessageBox>
#include <QPushButton>
#include <QWebSocket>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QInputDialog>
#include <QLineEdit>
#include <QCompleter>
#include <QFormLayout>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QToolTip>

namespace Ui {
class Equipment;
}

class Equipment : public QWidget
{
    Q_OBJECT

public:
    explicit Equipment(QWidget *parent = nullptr);
    ~Equipment();
   //  void closeEvent(QCloseEvent *event);

private slots:
    void on_tableView_equipment_clicked(const QModelIndex &index);

    void on_pb_add_clicked();
    void database_submit(QSqlTableModel *model_d);


    void on_pb_select_clicked();
    void pb_enter_clicked();
    void pb_cancel_clicked();


    void SlotMenuClicked(QModelIndex index);
    void add_status_Clicked(QModelIndex index);
    void CreateMenu(QPoint pos);


    void on_pb_delete_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pb_change_clicked();

private:
    Ui::Equipment *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    QSqlQueryModel *mode;
    QPushButton *pb_enter;
    QPushButton *pb_cancel;
     int  rowCount;
    int rowCount_c;
    QMenu *tableviewMenu;//菜单，需要头文件<QMenu>
    QAction *add_c_e;
    QAction *add_status;
    QString  name;
    QPoint p;
    QString e_c_name_add;
    void init_select_edit();
    void init_tableview_e();
    QCompleter *completer;
    QPushButton *add_row;
    QDialog dialog;  //增加传感器数据对话框
    QFormLayout *form; //增加传感器数据布局
    int add_rows_num;
    bool haserror = false; //增加传感器数据是否有错误
    int change_status=0; //修改和提交状态改变，默认0为修改







};

#endif // EQUIPMENT_H
