#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <QWidget>
#include <QDataStream>

using namespace std;


#define Filenamehw "Homework.dat"


//课程类

//---------------------------作业类----------------------------
class Homework
{
public:
    friend QDataStream& operator >>(QDataStream &in,Homework &read);//将信息读入
    //设置接口
    void SetName(QString name);
    //void SetAmount( amount);
    void SetContent(QString content);
    void SetLevel(QString level);
    void SetSubmission(QString submission);
    void SetFinish(QString finish);
    void SetYear(int year);
    void SetMonth(int month);
    void SetDate(int date);
    void SetHour(int hour);
    void SetMin(int min);

    //获取接口
    QString GetName();
    //Qstring GetAmount();
    QString GetContent();
    QString GetLevel();
    QString GetFinish();
    QString GetSubmission();
    bool GetMumber();
    int GetYear();
    int GetMonth();
    int GetDate();
    int GetHour();
    int GetMin();
    Homework(QString name = "nth", QString content = "nth", /*Qstring amount = "nth"*/ QString level = "unknown", QString finish = "未完成", QString submission = "unknown", int year = 0, int month = 0, int date = 0, int hour = 0, int min = 0)
    {
        _name = name;
        _content = content;
        //_amount = amount;
        _level = level;
        _submission = submission;
        _year = year;
        _month = month;
        _date = date;
        _hour = hour;
        _min = min;
        _finish = finish;
    }
private:
    QString _name;//哪一节课的作业
    QString _content;//作业内容
    //QString _amount;//作业量
    QString _level;//重要程度
    QString _finish;
    QString _submission;
    //截止时间部分
    int _year;
    int _month;
    int _date;
    int _hour;
    int _min;
};
//用于存储作业的链表节点
struct Nodehw
{
    Homework val;
    Nodehw* next;
};

//运算符重载
QDataStream& operator <<(QDataStream &out,Homework &add);//将新增作业输出
QDataStream& operator >>(QDataStream &in,Homework &read);//将信息读入
QDataStream& operator <<(QDataStream &out,Nodehw &t);
QDataStream& operator >>(QDataStream &in,Nodehw &n);
//-------------------------作业存储--------------------------

void SaveHomework(Nodehw* pNew);//保存作业

Nodehw* HomeworkFetch(void);//读取存储空间中的作业

Nodehw* HomeworkArrange(Nodehw* pHead);

void Swap(Nodehw* current);

void DeleteHomework(int n);

void ChangeHomework(int n);

#endif // HOMEWORK_H
