#ifndef SYSTEMSET_H
#define SYSTEMSET_H

#include <QWidget>

namespace Ui {
class SystemSet;
}

class SystemSet : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSet(QWidget *parent = nullptr);
    ~SystemSet();

private:
    Ui::SystemSet *ui;
};

#endif // SYSTEMSET_H
