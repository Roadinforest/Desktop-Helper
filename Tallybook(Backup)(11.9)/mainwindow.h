#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLCDNumber>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
 //   QLCDNumber* Lcd;
    QTimer *Timer;
//    QMenu *in;
//    QMenu *out;

public slots:
    void switchPage();//切换页面
    void change();//时间改变
    void visiable();//小日历的可见与否
    void Save();//存储数据
    void Clear();//将数据全部清除
    void Table();//将表格显示
    void TableClear();//清空表格
    void ShowPie();//展示饼状图
    void ShowSpline();//展示曲线图的窗口
    void ChangeColor();//改变背景底色
    void ChangeFont();//改变字体
 //   void paintEvent(QPaintEvent * ev);

};
#endif // MAINWINDOW_H
