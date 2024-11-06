#include "Course.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>

//运算符重载部分
QDataStream& operator <<(QDataStream &out,Course &add)//输出新增
{
    out << add.GetX() << add.GetY1() << add.GetY2() << add.GetScore()
        << add.GetName() << add.GetRoom() << add.GetTeach() << add.GetNote();
    qDebug() << add.GetX() << add.GetY1() << add.GetY2() << add.GetY2() << add.GetScore()
        << add.GetName() << add.GetRoom() << add.GetTeach() << add.GetNote();
    return out;
}

QDataStream& operator >>(QDataStream &in,Course &n)//读入数据
{
    in >> n._x >> n._y1 >> n._y2 >> n._score >> n._classname >> n._classroom >> n._teacher >> n._note;
    qDebug()<< n._x << n._y1 << n._y2 << n._score << n._classname << n._classroom << n._teacher << n._note;
    return in;
}

QDataStream& operator <<(QDataStream &out,Nodecs* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Nodecs* &n)
{
    in >> n->val;
    return in;
}

QString Course::GetName()
{
    return _classname;
}

QString Course::GetRoom()
{
    return _classroom;
}

QString Course::GetTeach()
{
    return _teacher;
}

QString Course::GetNote()
{
    return _note;
}

int Course::GetScore()
{
    return _score;
}

int Course::GetX()
{
    return _x;
}

int Course::GetY1()
{
    return _y1;
}

int Course::GetY2()
{
    return _y2;
}


void Course::SetName(QString classname)
{
    _classname = classname;
}

void Course::SetRoom(QString classroom)
{
    _classroom = classroom;
}

void Course::SetTeach(QString teacher)
{
    _teacher = teacher;
}

void Course::SetNote(QString note)
{
    _note = note;
}

void Course::SetScore(int score)
{
    _score = score;
}

void Course::SetX(int x)
{
    _x = x;
}

void Course::SetY1(int y1)
{
    _y1 = y1;
}

void Course::SetY2(int y2)
{
    _y2 = y2;
}

void SaveCourse(Nodecs* pNew)
{
    qDebug()<<"Enter!!!";
    //pNew是给入的暂时链表的头结点

    //几个基本步骤：
    //1.将指针指向临时存储的链表的最后一个
    //2.得到数据文件中存储的数据
    //3.将两个链表进行拼接

    //步骤2.得到数据文件中存储的数据
    //    QDataStream finout(&file);
    Nodecs* pointer = NULL;
    Nodecs* pHead = NULL;
    //准备读取数据文件中的头结点
    Nodecs* Each = new Nodecs;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    QFile file(Filenamecs);
    file.open(QFile::ReadOnly);
    QDataStream fout(&file);
    if(fout.atEnd())
    {
        qDebug()<<"Nothing";
    }
    while (!fout.atEnd())
    //这里是取出,其实每一步都是在重新取出东西
    //运算符重载，在这里就非常好咯
    {
        qDebug()<<"Here 1:read";
        fout>>Each;
        //每一个结点，只有刚开始的时候给它分配动态内存，之后它才有地方可以存
        if (i == 0)
        {
            pHead = Each;//将pHead进行初始化
            pointer = pHead;
        }
        else if (i > 0)
        {
            pointer->next = Each;
            pointer = Each;
        }//千万注意这里要用尾插法取出！！！
        i++;
        Each = new Nodecs;
        Each->next = NULL;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }

    delete Each;
    qDebug()<<"The pHead in file";


    //步骤1.将指针指向临时存储的链表的最后一个

    //刚开始的时候必须要将Node分配到NULL，否则它随便指到一个内存，那就完蛋啦
    //将pointer指向临时链表的最后结点,并且得到临时链表中的总个数range
    if (pNew)
    {//如果传进来的临时链表的头结点存在
        qDebug()<<"pNew存在";
        pointer = pNew;
        int range = 0;
        while (pointer)
        {
            range++;
            pointer = pointer->next;
        }
        pointer = pNew;
        qDebug()<<"共有"<<range<<"组数据进入";
    }
    else if (!pNew)
    {//如果这个头结点并不存在
        qDebug() << "Error:链表为空" << Qt::endl;
            return ;//因为是一个void函数，所以return后面并没有参数
    }
    qDebug()<<"Here is the new list";



    //步骤三。将两个链表进行拼接
    qDebug()<<"Did it have";

    pointer->next= pHead;
    qDebug()<<"Finish";

    qDebug()<<"Here";
    Nodecs* Np = pNew;
    qDebug()<<"The list prepare to be saved";
    file.close();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    //截断，因为我们要从头开始写
    {
        qDebug() << "Error2:文件打开错误！！！" << Qt::endl;
    }
    QDataStream fin(&file);
    i = 1;
    while (Np)
    {
        qDebug()<<Np->val.GetName()<<"课程名称存入";
        qDebug()<<"Here 2:write";
        fin<<Np;
        Np = Np->next;
        i++;
    }
    file.close();
    qDebug() << "成功保存!!!" << Qt::endl;
}

Nodecs* CourseFetch()
{
    QFile file(Filenamecs);
    file.open(QIODevice::ReadOnly);
    QDataStream fout(&file);

    if (fout.atEnd())//防止用户初次使用时文件为空
    {
        return NULL;
    }

    Nodecs* pHead = NULL;
    //准备读取数据文件中的头结点
    Nodecs* Each = new Nodecs;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    Nodecs* pointer = NULL;
    while (!fout.atEnd())
    {

        fout>>Each;

        //每一个结点，只有刚开始的时候给它分配动态内存，之后它才有地方可以存
        if (i == 0)
        {
            pHead = Each;//将pHead进行初始化
            pointer = pHead;
        }
        else if (i > 0)
        {
            pointer->next = Each;
            pointer = Each;
        }//千万注意这里要用尾插法取出！！！
        i++;
        Each = new Nodecs;
        Each->next = NULL;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    delete Each;
    qDebug()<<"Fetch finished(Course)";
    return pHead;
}

Nodecs* CourseSearch(QString name)
{
    Nodecs* Head = CourseFetch();
    Nodecs* current = Head;
    while(current)
    {
        if(current->val.GetName() == name)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
