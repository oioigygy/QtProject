#ifndef LINEMANAGE_H
#define LINEMANAGE_H

#include <QWidget>

namespace Ui {
class LineManage;
}

class LineManage : public QWidget
{
    Q_OBJECT

public:
    explicit LineManage(QWidget *parent = nullptr);
    ~LineManage();

private:
    Ui::LineManage *ui;
};

#endif // LINEMANAGE_H
