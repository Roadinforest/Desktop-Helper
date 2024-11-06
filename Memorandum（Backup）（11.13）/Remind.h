#ifndef REMIND_H
#define REMIND_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <QWidget>
#include <QDataStream>

using namespace std;

#define Filenamerm "Remind.dat"

class Remind
{
    friend QDataStream& operator >>(QDataStream &in,Remind &read);
public:
    //----------------写入---------------
    void QDBUG();
    void SetOrganizer(QString orginazer);
    void SetAcConnent(QString acconnent);
    void SetYear(int year);
    void SetMonth(int month);
    void SetDate(int date);
    void SetHour(int hour);
    void SetMin(int min);
    //----------------读取---------------
    QString GetOrganizer();
    QString GetAcContent();
    int GetYear();
    int GetMonth();
    int GetDate();
    int GetHour();
    int GetMin();
    bool GetMumber();
    //------------constructor------------、
    Remind(QString orginazer = "unknown", QString accontent = "unknown", int year = 0, int month = 0, int date = 0, int hour = 0, int min = 0)
    {
        organizer_ = orginazer;
        accontent_ = accontent;
        year_ = year;
        month_ = month;
        date_ = date;
        hour_ = hour;
        min_ = min;
    }
private:
    QString organizer_;
    QString accontent_;
    int year_;
    int month_;
    int date_;
    int hour_;
    int min_;
};

struct Noderm
{
    Remind val;
    Noderm* next;
};

//运算符重载
QDataStream& operator <<(QDataStream &out,Remind &add);//将新增作业输出
QDataStream& operator >>(QDataStream &in,Remind &read);//将信息读入
QDataStream& operator <<(QDataStream &out,Noderm &t);
QDataStream& operator >>(QDataStream &in,Noderm &n);

void SaveRemind(Noderm* Rnew);

Noderm* RemindFetch();

Noderm* RemindArrange(Noderm* pHead);

void Swap(Noderm* current);

void DeleteRemind(int n);

#endif // REMIND_H
