#ifndef TITLEBAR_SHOW_H
#define TITLEBAR_SHOW_H

#include <QWidget>
#include "basetitlebar.h"
namespace Ui {class MainWindow;}
class TitleBarShow : public BaseWindow
{
    Q_OBJECT

public:
    TitleBarShow(QWidget *parent = 0);
    ~TitleBarShow();
    void initTitleBar();

protected:

};

#endif // TITLEBAR_SHOW_H
