#ifndef ANALYSISEQUIP_H
#define ANALYSISEQUIP_H

#include <QWidget>

namespace Ui {
class AnalysisEquip;
}

class AnalysisEquip : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisEquip(QWidget *parent = nullptr);
    ~AnalysisEquip();

private:
    Ui::AnalysisEquip *ui;
};

#endif // ANALYSISEQUIP_H
