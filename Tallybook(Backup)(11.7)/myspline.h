#ifndef MYSPLINE_H
#define MYSPLINE_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>

namespace Ui {
class MySpline;
}

class MySpline : public QWidget
{
    Q_OBJECT

public:
    explicit MySpline(QWidget *parent = nullptr);
    ~MySpline();

private:
    Ui::MySpline *ui;
    QChart *mChart;


};

#endif // MYSPLINE_H
