#ifndef PEOPLEMANAGE_H
#define PEOPLEMANAGE_H

#include <QWidget>

namespace Ui {
class PeopleManage;
}

class PeopleManage : public QWidget
{
    Q_OBJECT

public:
    explicit PeopleManage(QWidget *parent = nullptr);
    ~PeopleManage();

private:
    Ui::PeopleManage *ui;
};

#endif // PEOPLEMANAGE_H
