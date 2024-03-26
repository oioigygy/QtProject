#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QWidget>

namespace Ui {
class DeviceStatus;
}

class DeviceStatus : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceStatus(QWidget *parent = nullptr);
    ~DeviceStatus();

private:
    Ui::DeviceStatus *ui;
    void init_status();
};

#endif // DEVICESTATUS_H
