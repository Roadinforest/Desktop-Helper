#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <QWidget>
#include <QDataStream>
using namespace std;

#define Filenamecs "Course.dat"

class Course
{
public:
    friend QDataStream& operator >>(QDataStream &in,Course &n);
    QString GetName();
    QString GetRoom();
    QString GetTeach();
    QString GetNote();
    int GetScore();
    int GetX();
    int GetY1();
    int GetY2();
    void SetName(QString classname);
    void SetRoom(QString classroom);
    void SetTeach(QString teacher);
    void SetNote(QString note);
    void SetScore(int score);
    void SetX(int x);
    void SetY1(int y1);
    void SetY2(int y2);
    Course(int x = 0, int y1 = 0, int y2 = 0, int score = 0, QString classname = "classname", QString teacher = "teacher", QString classroom = "classroom", QString note = "note")
    {
        _x = x;
        _y1 = y1;
        _y2 = y2;
        _score = score;
        _classname = classname;
        _teacher = teacher;
        _classroom = classroom;
        _note = note;
    }

private:
    int _x;//横坐标，周数本身
    int _y1;//开始节数
    int _y2;//结束节数
    int _score;//学分
    //int _z1 //开始周数
    //int _z2 //结束周数
    QString _classname;//课程名
    QString _teacher;//老师
    QString _classroom;//教室
    QString _note;//备注

};

struct Nodecs
{
    Course val;
    Nodecs* next;
};

//运算符重载部分
QDataStream& operator <<(QDataStream &out,Course &add);
QDataStream& operator >>(QDataStream &in,Course &n);
QDataStream& operator <<(QDataStream &out,Nodecs* &t);
QDataStream& operator >>(QDataStream &in,Nodecs* &n);

//service
void SaveCourse(Nodecs* Cnew);

Nodecs* CourseFetch();

Nodecs* CourseSearch(QString name);

#endif // COURSE_H
