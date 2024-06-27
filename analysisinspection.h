#ifndef ANALYSISINSPECTION_H
#define ANALYSISINSPECTION_H

#include <QWidget>

namespace Ui {
class AnalysisInspection;
}

class AnalysisInspection : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisInspection(QWidget *parent = nullptr);
    ~AnalysisInspection();

private:
    Ui::AnalysisInspection *ui;
};

#endif // ANALYSISINSPECTION_H
