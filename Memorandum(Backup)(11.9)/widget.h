#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Qstring>
#include "Homework.h"

#define CourseNums 13 //想通过宏常量达到后续修改的目的，但考虑到表格大小无法变化......

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

//-----------------------------友元---------------------------------


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //主界面切换部分
    void on_btn_EXP_clicked();//切换到welcome&exp界面

    void on_btn_course_clicked();//切换到课程界面

    void on_btn_homework_clicked();//切换到作业界面

    void on_btn_reminder_clicked();//切换到提醒界面

    void on_btn_setting_clicked();//切换到设置界面

    void on_btn_quit_clicked();//退出程序
    //---------------------------------------课程表----------------------------------
    void AddCourse();

    void ShowCourse();

    void ClearCourse();

    void on_savecourse_clicked();

    void on_btn_addcourse_clicked();

    void on_btn_showCourseTable_clicked();
    //--------------------------------------作业界面------------------------------------------
    //展示模块
    void on_btn_showHW_2_clicked();//作业界面下展示界面
    //添加模块
    void on_btn_addHW_2_clicked();//作业界面下添加作业

    void on_savehomework_clicked();//作业添加保存按钮

    void AddHomework();//添加作业

    void ShowHomework();//展示作业

    void ClearHomework();//清空展示表（防止错误显示）

    void on_btn_changeHW_2_clicked();//作业界面下修改（小窗）
    //--------------------------------------提醒界面-------------------------------------------
    void on_btn_addAC_3_clicked();//提醒界面下添加活动界面

    void on_btn_showAC_3_clicked();//提醒界面下展示界面

    void on_btn_changeAC_3_clicked();//提醒界面下修改界面

    void AddRemind();

    void ShowRemind();

    void ClearRemind();







    void on_saveremind_clicked();



    void on_btn_change_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
