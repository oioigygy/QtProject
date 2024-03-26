#ifndef TASKMANAGE_H
#define TASKMANAGE_H

#include <QWidget>

namespace Ui {
class TaskManage;
}

class TaskManage : public QWidget
{
    Q_OBJECT

public:
    explicit TaskManage(QWidget *parent = nullptr);
    ~TaskManage();

private:
    Ui::TaskManage *ui;
};

#endif // TASKMANAGE_H
