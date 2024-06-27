#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <QWidget>

namespace Ui {
class SystemLog;
}

class SystemLog : public QWidget
{
    Q_OBJECT

public:
    explicit SystemLog(QWidget *parent = nullptr);
    ~SystemLog();

private:
    Ui::SystemLog *ui;
};

#endif // SYSTEMLOG_H
