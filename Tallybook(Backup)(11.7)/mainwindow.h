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
    QLCDNumber* Lcd;
    QTimer *Timer;
//    QMenu *in;
//    QMenu *out;

public slots:
    void switchPage();
    void change();
    void visiable();
    void Save();
    void Clear();
    void Table();
    void TableClear();
    void ShowPie();
    void ShowSpline();
    void ChangeColor();

};
#endif // MAINWINDOW_H
