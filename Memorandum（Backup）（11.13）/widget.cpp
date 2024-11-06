#include "widget.h"
#include "ui_widget.h"
#include "fix.h"
#include "fixre.h"
#include "Course.h"
#include "Homework.h"
#include "Remind.h"
#include "fixcs.h"
#include "notice.h"
#include <iostream>
#include <QFile>
#include <QDataStream>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->MainStacked->setCurrentIndex(0);
    //----------------------------设置部分初始化------------------------------
    ui->coursenums->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    //----------------------------课程部分初始化------------------------------
    ui->Xedit->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-7]{1}")));
    ui->Y1edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    ui->Y2edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    int nums = GetUserCoursenums();
    ui->CourseTable->setRowCount(nums);//便于设置更改
    ui->CourseTable->setColumnCount(7);
    ui->CourseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
    ui->CourseTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
    ui->CourseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoswitch->hide();
    ui->infoteacher->isReadOnly();
    ui->infoteacher->setFont(QFont("华文新魏",16));
    ui->inforoom->isReadOnly();
    ui->inforoom->setFont(QFont("华文新魏",16));
    ui->infoscore->isReadOnly();
    ui->infoscore->setFont(QFont("华文新魏",16));
    ui->infonote->isReadOnly();
    ui->infonote->setFont(QFont("华文新魏",16));
    ShowCourse();
    //----------------------------作业部分初始化------------------------------
    ui->HomeworkStacked->setCurrentIndex(0);
    ui->HomeworkTable_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->HomeworkTable_1->setColumnWidth(0,95);
    ui->HomeworkTable_1->setColumnWidth(1,220);
    ui->HomeworkTable_1->setColumnWidth(2,145);
    ui->HomeworkTable_1->setColumnWidth(3,60);
    ui->HomeworkTable_1->setColumnWidth(4,125);
    ui->HomeworkTable_1->setColumnWidth(5,75);
    ui->levelhide->hide();
    ui->statushide->hide();
    ShowHomework();
    //----------------------------提醒部分初始化-------------------------------
    ui->RemindStacked->setCurrentIndex(0);
    ui->RemindTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->RemindTable->setColumnWidth(0,150);
    ui->RemindTable->setColumnWidth(1,360);
    ui->RemindTable->setColumnWidth(2,150);
    ShowRemind();
}

Widget::~Widget()
{
    delete ui;
}

int Widget::GetUserCoursenums()
{
    QFile file(Coursenums);
    file.open(QIODevice::ReadOnly);
    if(file.atEnd())
    {
        return 13;
    }
    else
    {
        int num;
        QByteArray array = file.readAll();
        num = array.toInt();
        return num;
    }
}

void Widget::SetUserCoursenums()
{
    QFile file(Coursenums);
    file.open(QIODevice::WriteOnly);
    file.write(ui->coursenums->text().toUtf8());
    file.close();
}

void Widget::on_coursenumsqd_clicked()
{
    if(!ui->coursenums->text().isEmpty())
    {
        SetUserCoursenums();
        int nums = GetUserCoursenums();
        ui->CourseTable->setRowCount(nums);
        ui->CourseTable->update();
    }
}

//------------------主界面切换------------------
void Widget::on_btn_EXP_clicked()
{
    ui->CourseTable->update();
    ui->MainStacked->setCurrentIndex(0);
}

void Widget::on_btn_course_clicked()
{
    ui->MainStacked->setCurrentIndex(1);
}


void Widget::on_btn_homework_clicked()
{
    ui->HomeworkTable_1->update();
    ui->MainStacked->setCurrentIndex(2);
}


void Widget::on_btn_reminder_clicked()
{
    ui->RemindTable->update();
    ui->MainStacked->setCurrentIndex(3);
}


void Widget::on_btn_setting_clicked()
{
    ui->MainStacked->setCurrentIndex(4);
}


void Widget::on_btn_quit_clicked()
{
    QApplication* app;
    app->exit(0);
}

//------------------------课程部分-----------------------
void Widget::ClearCourse()
{
    ui->CourseTable->clear();
}

void Widget::AddCourse()
{
    int x;//横坐标，周数本身
    int y1;//开始节数
    int y2;//结束节数
    int score;//学分
    //int z1 //开始周数
    //int z2 //结束周数
    QString classname;//课程名
    QString teacher;//老师
    QString classroom;//教室
    QString note;//备注
    classname = ui->csnameedit->text();
    teacher = ui->teachedit->text();
    classroom = ui->roomedit->text();
    note = ui->noteedit->toPlainText();
    x = ui->Xedit->text().toInt();
    qDebug()<<"添加的数据"<<x<<"周";
    y1 = ui->Y1edit->text().toInt();
    qDebug()<<"添加的数据"<<x<<"节";
    y2 = ui->Y2edit->text().toInt();
    qDebug()<<"添加的数据"<<x<<"节";
    score = ui->scoreedit->text().toInt();
    Course* add = new Course(x,y1,y2,score,classname,teacher,classroom,note);
    Nodecs* Cnew = new Nodecs;
    Cnew->val = *add;
    Cnew->next = NULL;
    SaveCourse(Cnew);
    ShowCourse();
}

void Widget::ShowCourse()
{
    ClearCourse();
    qDebug()<<"showing course";
    Nodecs* Head = CourseFetch();
    Nodecs* Current = Head;
    while(Current)
    {
        //qDebug()<<++i<<"次course while";
        int x = Current->val.GetX()-1;
        qDebug()<<"课程名"<<Current->val.GetName();
        qDebug()<<"周"<<x;
        int y1 = Current->val.GetY1()-1;
        qDebug()<<"第"<<y1<<"节课开始";
        int y2 = Current->val.GetY2()-1;
        qDebug()<<"第"<<y2<<"节课开始";
        qDebug()<<"finishing getting course info";
        for(int i = y1; i <= y2; i++)
        {
            QString classname = Current->val.GetName();
            qDebug()<<classname;
            QTableWidgetItem* iclassname = new QTableWidgetItem(classname);
            ui->CourseTable->setItem(i,x,iclassname);
            ui->CourseTable->item(i,x)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->CourseTable->item(i,x)->setFont(QFont("华文新魏",16));
            qDebug()<<"finish setting course text";
            iclassname = NULL;
        }
        Current = Current->next;
    }

    ui->CourseTable->update();
}

void Widget::on_search_clicked()
{
    ui->infoswitch->show();
    if(!ui->searchname->text().isEmpty())
    {
        QString name = ui->searchname->text();
        Nodecs* answer = CourseSearch(name);
        if(answer)
        {
            QString teacher;
            QString room;
            QString score;
            QString note;
            teacher = answer->val.GetTeach();
            room = answer->val.GetRoom();
            score = QString::number(answer->val.GetScore());
            note = answer->val.GetNote();
            ui->infoteacher->setText(teacher);
            ui->inforoom->setText(room);
            ui->infoscore->setText(score);
            ui->infonote->setText(note);
            ui->infoswitch->setCurrentIndex(1);
        }
        else
        {
            ui->infoswitch->setCurrentIndex(0);
        }
    }

}

void Widget::on_btn_showCourseTable_clicked()
{
    ui->CourseTable->update();
    ui->CourseStacked->setCurrentIndex(0);
}

void Widget::on_btn_change_clicked()
{
    ShowCourse();
    ui->CourseTable->update();
    ui->CourseStacked->setCurrentIndex(0);
    fixcs* change = new fixcs;
    change->show();
}

void Widget::on_savecourse_clicked()
{
    if(!(ui->csnameedit->text().isEmpty())&&(!(ui->Xedit->text().isEmpty()))
        &&(!(ui->Y1edit->text().isEmpty()))&&(!(ui->Y2edit->text().isEmpty()))
        &&(ui->Y1edit->text().toInt())<=(ui->Y2edit->text().toInt()))
    {
        AddCourse();
        ui->csnameedit->text().clear();
        ui->teachedit->text().clear();
        ui->scoreedit->text().clear();
        ui->roomedit->text().clear();
        ui->Xedit->text().clear();
        ui->Y1edit->text().clear();
        ui->Y2edit->text().clear();
        ui->noteedit->toPlainText().clear();
        ui->CourseStacked->setCurrentIndex(0);
    }

}


void Widget::on_btn_addcourse_clicked()
{
    ui->CourseStacked->setCurrentIndex(1);
}

void Widget::on_btn_info_clicked()
{
    ui->CourseStacked->setCurrentIndex(2);
}

//-----------------------------------------作业界面-----------------------------------------------
//展示作业列表
void Widget::on_btn_showHW_2_clicked()
{
    ShowHomework();
    ui->HomeworkTable_1->update();
    ui->HomeworkStacked->setCurrentIndex(0);
}

//添加模块
void Widget::AddHomework()
{
    QString name;
    QString content;
    //QString amount;
    QString level;
    QString finish;
    QString submission;
    int year;
    int month;
    int date;
    int hour;
    int min;
    name = ui->nameedit->text();
    content = ui->contentedit->toPlainText();
    submission = ui->submissionedit->text();
    qDebug()<<submission;
    year = ui->DDL->date().year();
    month = ui->DDL->date().month();
    date = ui->DDL->date().day();
    hour = ui->DDL->time().hour();
    min = ui->DDL->time().minute();
    //重要程度
    if(ui->level->isChecked())
    {
        level = "重要";
    }
    else if(ui->level_2->isChecked())
    {
        level = "一般";
    }
    else if(ui->level_3->isChecked())
    {
        level = "不重要";
    }
    //完成情况
    if(ui->status->isChecked())
    {
        finish = "未完成";
    }
    else if(ui->status_2->isChecked())
    {
        finish = "已完成";
    }
    //时间不会为空，但是课程名和作业内容必须有值，其他部分不填就算了
    Homework* hw_add = new Homework(name,content,level,finish,submission,year,month,date,hour,min);
    qDebug()<< hw_add->GetSubmission();
    Nodehw* pNew = new Nodehw;
    pNew->val = *hw_add;
    pNew->next = NULL;
    SaveHomework(pNew);
    ShowHomework();
}

void Widget::ShowHomework()
{
    ClearHomework();
    qDebug()<<"start to show homework";
    Nodehw* Head = HomeworkArrange(HomeworkFetch());
    Nodehw* Current = Head;
    int i = 0;
    while(Current)
    {
        qDebug()<<"第"<<++i<<"次进去showhome while";
        qDebug()<<Current;
        QString name = Current->val.GetName();
        qDebug()<<name;
        QString content = Current->val.GetContent();
        QString level = Current->val.GetLevel();
        QString finish = Current->val.GetFinish();
        QString submission = Current->val.GetSubmission();
        //qDebug()<<submission;
        int year = Current->val.GetYear();
        int month = Current->val.GetMonth();
        int date = Current->val.GetDate();
        int hour = Current->val.GetHour();
        int min = Current->val.GetMin();
        ui->HomeworkTable_1->setRowCount((ui->HomeworkTable_1->rowCount()+1));
        int row = (ui->HomeworkTable_1->rowCount())-1;
        QTableWidgetItem* iname = new QTableWidgetItem(name);
        QTableWidgetItem* icontent = new QTableWidgetItem(content);
        QTableWidgetItem* iDDL = new QTableWidgetItem(QString::number(year)+"-"+QString::number(month)+"-"+QString::number(date)
                                                      +"-"+QString::number(hour)+":"+QString::number(min));
        QTableWidgetItem* ilevel = new QTableWidgetItem(level);
        QTableWidgetItem* isubmission = new QTableWidgetItem(submission);
        QTableWidgetItem* ifinish= new QTableWidgetItem(finish);
        ui->HomeworkTable_1->setItem(row, 0, iname);
        ui->HomeworkTable_1->setItem(row, 1, icontent);
        ui->HomeworkTable_1->setItem(row, 2, iDDL);
        ui->HomeworkTable_1->setItem(row, 3, ilevel);
        ui->HomeworkTable_1->setItem(row, 4, isubmission);
        ui->HomeworkTable_1->setItem(row, 5, ifinish);
        for(int i = 0; i <= 5; i++)
        {
            if(i==3)
            {
                ui->HomeworkTable_1->item(row, i)->setFont(QFont("华文新魏",12));
                continue;
            }
            ui->HomeworkTable_1->item(row, i)->setFont(QFont("华文新魏",14));
        }
        Current = Current->next;
    }
    ui->HomeworkTable_1->update();
    //qDebug()<<"作业界面成功更新";
}

void Widget::ClearHomework()
{
    ui->HomeworkTable_1->clear();
    ui->HomeworkTable_1->setRowCount(0);
}

void Widget::on_savehomework_clicked()//添加保存
{
    //时间不会为空，但是课程名和作业内容必须有值，其他部分不填就算了
    if(!(ui->nameedit->text().isEmpty())&&(!(ui->contentedit->toPlainText().isEmpty())))
    {
        AddHomework();
        ui->nameedit->clear();
        ui->contentedit->clear();
        ui->DDL->clear();
        ui->submissionedit->clear();
        ui->levelhide->setChecked(true);
        ui->statushide->setChecked(true);
        ui->HomeworkStacked->setCurrentIndex(0);
    }


}

void Widget::on_btn_addHW_2_clicked()
{
    ui->HomeworkStacked->setCurrentIndex(1);
}

void Widget::on_btn_changeHW_2_clicked()
{
    ShowHomework();
    ui->HomeworkStacked->setCurrentIndex(0);
    Fix* change = new Fix;
    change->show();
}


//------------------------------------------------提醒部分-----------------------------------------------
//提醒界面切换
void Widget::on_btn_addAC_3_clicked()
{
    ui->RemindStacked->setCurrentIndex(1);
}

void Widget::on_btn_showAC_3_clicked()
{
    ShowRemind();
    ui->RemindTable->update();
    ui->RemindStacked->setCurrentIndex(0);
}

void Widget::on_btn_changeAC_3_clicked()
{
    ShowRemind();
    ui->RemindStacked->setCurrentIndex(0);
    FixRE* change_ac = new FixRE;
    change_ac->show();
}

void Widget::ClearRemind()
{
    ui->RemindTable->clear();
    ui->RemindTable->setRowCount(0);
    qDebug()<<"提醒清屏完成";
}

void Widget::AddRemind()
{
    QString organizer;
    QString accontent;
    int year;
    int month;
    int date;
    int hour;
    int min;
    organizer = ui->organizer->text();
    accontent = ui->activity->toPlainText();
    year = ui->appointtime->date().year();
    month = ui->appointtime->date().month();
    date = ui->appointtime->date().day();
    hour = ui->appointtime->time().hour();
    min = ui->appointtime->time().minute();
    Remind* add = new Remind(organizer, accontent, year, month, date, hour, min);
    Noderm* Rnew = new Noderm;
    Rnew->val = *add;
    Rnew->next = NULL;
    SaveRemind(Rnew);
    ShowRemind();
}
void Widget::ShowRemind()
{
    //qDebug()<<"1";
    ClearRemind();
    Noderm* Head = RemindFetch();
    //qDebug()<<"2";
    Noderm* Current = Head;
    int i = 0;
    while(Current)
    {
        qDebug()<<++i<<"进入remindwhile";
        qDebug()<<Current;
        QString organizer;
        QString accontent;
        int year;
        int month;
        int date;
        int hour;
        int min;
        qDebug()<<"a";
        Current->val.QDBUG();
        organizer = Current->val.GetOrganizer();
        qDebug()<<"f";
        accontent = Current->val.GetAcContent();
        year = Current->val.GetYear();
        //qDebug()<<"e";
        month = Current->val.GetMonth();
        date = Current->val.GetDate();
        hour = Current->val.GetHour();
        min = Current->val.GetMin();
        int row = ui->RemindTable->rowCount();
        ui->RemindTable->setRowCount(row+1);
        //qDebug()<<"b";
        QTableWidgetItem* iorganizer = new QTableWidgetItem(organizer);
        QTableWidgetItem* iaccontent = new QTableWidgetItem(accontent);
        QTableWidgetItem* iappointedtime = new QTableWidgetItem(QString::number(year)+"-"+QString::number(month)
                                                                +"-"+QString::number(date)+"-"+QString::number(hour)+":"+QString::number(min));
        ui->RemindTable->setItem(row, 0, iorganizer);
        ui->RemindTable->setItem(row, 1, iaccontent);
        ui->RemindTable->setItem(row, 2, iappointedtime);
        //qDebug()<<"c";
        for(int i = 0; i <= 2; i++)
        {
            ui->RemindTable->item(row, i)->setFont(QFont("华文新魏",14));
        }
        //qDebug()<<"d";
        //qDebug()<<i<<":"<<Current;
        Current = Current->next;
        //qDebug()<<"After"<<i<<":"<<Current;
        if(Current==NULL){
            qDebug()<<"This is the nullptr!!!";
        }
    }
    ui->RemindTable->update();
    qDebug()<<"提醒界面更新成功";

}
void Widget::on_saveremind_clicked()
{
    if(!(ui->activity->toPlainText().isEmpty()))//组织方就算了吧，有个活动起码要
    {
        AddRemind();
        ui->activity->clear();
        ui->organizer->clear();
        ui->appointtime->clear();
        ui->RemindStacked->setCurrentIndex(0);
    }
}
















