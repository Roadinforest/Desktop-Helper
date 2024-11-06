#ifndef TALLYBOOK_H
#define TALLYBOOK_H


#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<QDataStream>
#include<QString>

#define Filename1 "BillDate.dat"
#define Outlay 0//支出
#define Income 1//收入

class Bill {
private:
    int year_;
    int month_;
    int date_;

    int value_;//The value of the account
    QString note_=" ";

    int case_=0;//The case of income or outlay

public:
    Bill(int value=0, int year=0, int month=0, int date=0,
         QString note="Nothing", int Case = 0) {
        value_ = value;
        year_ = year;
        month_ = month;
        date_=date;
        note_ = note;
        case_ = Case;
    }
    //函数重载，方便操作
    void ShowRecord(void);

    friend QDataStream& operator >>(QDataStream &in,Bill &t);
    //返回一个流的引用值，这个设计是非常科学的
    friend QDataStream& operator <<(QDataStream &out,Bill &t);

    //一堆接口
    //The reader获取数据
    int GetYear(void);
    int GetMonth(void);
    int GetDate(void);
    int GetHour(void);
    int GetMin(void);
    int GetValue(void);
    int GetCase(void);
    QString GetNote(void);

    //The writer写入数据
    void SetYear(int year);
    void SetMonth(int month);
    void SetDate(int date);
    void SetHour(int hour);
    void SetMin(int min);
    void SetValue(int value);
    void SetCase(int Case);
    void SetNote(QString name);
};

//链表相关
struct Node1 {
    Bill value;
    Node1* pNext;
};//创建一个结点

QDataStream& operator <<(QDataStream &out,Node1* &t);

QDataStream& operator >>(QDataStream &in,Node1* &t);


//----------service----------

void SaveList1(Node1* pHead);
//保存临时存储的链表

void BillAdd(Bill n);
//添加账单的主调函数

void BillDelete(void);
//删除对应num序号对应的结点

Node1* BillFetch(void);
//返回数据文件中存储的所有数据的链表的头结点

void BillChange(void);
//修改某条账单的数据

Node1* BillArrange(Node1* given);
//返回一个已经按照时间顺序排好的链表头结点

void BillReplace(Node1* pHead);
//将数据文件中的数据以给入的链表替代

void Swap(Node1* current);
//将该结点与后面一个结点进行替换

bool IsRun(int year);
//判断输入年份是否为闰年

int ReturnDay(int year,int month);
//根据年份是否为闰年，以及月份返回该月应该有多少天

void BillClear();
//----------service----------

//----------view----------


void BillModify(void);
//修改账单的主调函数

void BillStatistics(void);
//统计账单的主调函数

void BillQuit(void);
//退出记账本的主调函数

void ShowList1(Node1* pHead);
//显示给入的链表数据

void TallyBook(void);
//记账本的菜单界面

void BillShow(void);
//从数据文件中读取数据并且进行显示

void ShowYear(int year);
//显示year年份的所有账单

void ShowMonth(int year,int month);
//显示year年份下month月份的账单

void ShowDate(int year, int month,int date);
//显示year年份下month月份day天的账单

//----------view---------



#endif // TALLYBOOK_H
