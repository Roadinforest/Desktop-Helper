#include "Homework.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "widget.h"
#include "fix.h"
//运算符重载部分
QDataStream& operator <<(QDataStream &out,Homework &add)//输出新增
{
    out<<add.GetName()<<add.GetContent()<<add.GetLevel()<<add.GetFinish()<<add.GetSubmission()<<add.GetYear()
        <<add.GetMonth()<<add.GetDate()<<add.GetHour()<<add.GetMin();
    return out;
}

QDataStream& operator >>(QDataStream &in,Homework &n)//读入数据
{
    in >> n._name >> n._content >> n._level >> n._finish >> n._submission
        >> n._year >> n._month >> n._date >> n._hour >> n._min;
    return in;
}

QDataStream& operator <<(QDataStream &out,Nodehw* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Nodehw* &n)
{
    in >> n->val;
    return in;
}

//课程类的接口

//作业类的接口
void Homework::SetSubmission(QString submission)
{
    _submission = submission;
}

void Homework::SetName(QString name)
{
    _name = name;
}

/*void Homework::SetAmount(QString amount)
{
    _amount = amount;
}*/

void Homework::SetLevel(QString level)
{
    _level = level;
}

void Homework::SetYear(int year)
{
    _year = year;
}

void Homework::SetMonth(int month)
{
    _month = month;
}

void Homework::SetDate(int date)
{
    _date = date;
}

void Homework::SetHour(int hour)
{
    _hour = hour;
}

void Homework::SetMin(int min)
{
    _min = min;
}

void Homework::SetContent(QString content)
{
    _content = content;
}

void Homework::SetFinish(QString finish)
{
    _finish = finish;
}

QString Homework::GetName()
{
    return _name;
}

/*QString Homework::GetAmount()
{
    return _amount;
}*/

QString Homework::GetLevel()
{
    return _level;
}

QString Homework::GetFinish()
{
    return _finish;
}

QString Homework:: GetSubmission()
{
    return _submission;
}

int Homework::GetYear()
{
    return _year;
}

int Homework::GetMonth()
{
    return _month;
}

int Homework::GetDate()
{
    return _date;
}

int Homework::GetHour()
{
    return _hour;
}

int Homework::GetMin()
{
    return _min;
}

QString Homework::GetContent()
{
    return _content;
}

bool Homework::GetMumber()
{
    if(sizeof(*this)==1)
    {
        return 0;
    }
    return 1;
}

//---------------------保存模块----------------------

//保存模块
void SaveHomework(Nodehw* pNew)
{


    qDebug()<<"Enter!!!";
    //pNew是给入的暂时链表的头结点

    //几个基本步骤：
    //1.将指针指向临时存储的链表的最后一个
    //2.得到数据文件中存储的数据
    //3.将两个链表进行拼接

    //步骤2.得到数据文件中存储的数据
    //    QDataStream finout(&file);
    Nodehw* pointer = NULL;
    Nodehw* pHead = NULL;
    //准备读取数据文件中的头结点
    Nodehw* Each = new Nodehw;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    QFile file(Filenamehw);
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
        Each = new Nodehw;
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
    Nodehw* Np = pNew;
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
        qDebug()<<"Here 2:write";
        fin<<Np;
        Np = Np->next;
        i++;
    }
    file.close();
    qDebug() << "成功保存!!!" << Qt::endl;
}

Nodehw* HomeworkFetch(void)
{

    QFile file(Filenamehw);
    file.open(QIODevice::ReadOnly);
    QDataStream fout(&file);

    if (fout.atEnd())//防止用户初次使用时文件为空导致返回空指针
    {
        qDebug() << "initial usage" << Qt::endl;
        QString name = "CrazyThu";
        QString content = "V Vkun_s 50";
        //QString amount;
        QString level = "重要";
        QString finish = "未完成";
        QString submission = "微信红包";
        int year = 9999;
        int month = 9;
        int date = 9;
        int hour = 9;
        int min = 9;
        Homework* Initial = new Homework(name,content,level,finish,submission,year,month,date,hour,min);
        Nodehw* Initialnode = new Nodehw;
        Initialnode->val = *Initial;
        Initialnode->next = NULL;
        return Initialnode;
    }

    Nodehw* pHead = NULL;
    //准备读取数据文件中的头结点
    Nodehw* Each = new Nodehw;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    Nodehw* pointer = NULL;
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
        Each = new Nodehw;
        Each->next = NULL;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    delete Each;
    qDebug()<<"Fetch finished";
    return pHead;
}

void Swap(Nodehw* current)
{
    Homework Tem = current->val;
    Homework Tem2 = current->next->val;
    current->val = Tem2;
    current->next->val = Tem;
}

Nodehw* HomeworkArrange(Nodehw* pHead)
{
    //创建辅助指针
    Nodehw* current = pHead;//此时current即为头指针，指向第一个节点
    int num = 0;
    //用于计算共有多少个结点
    while (current)
    {
        current = current->next;
        num++;
    }
    //for循环是冒泡排序第一层，while循环是冒泡排序第二层
    for (int i = 0; i < num - 1; i++)//冒泡思想，查找num-1次
    {
        current = pHead;//每次都从头开始找
        //cout << "第" << i + 1 << "次进入循环" << endl;//测试时使用
        while (current->next)
        {
            //获取相邻两个节点中所存储的时间数据
            int y1 = current->val.GetYear();
            int mo1 = current->val.GetMonth();
            int d1 = current->val.GetDate();
            int h1 = current->val.GetHour();
            int mi1 = current->val.GetMin();
            int y2 = current->next->val.GetYear();
            int mo2 = current->next->val.GetMonth();
            int d2 = current->next->val.GetDate();
            int h2 = current->next->val.GetHour();
            int mi2 = current->next->val.GetMin();
            //冒泡排序，年份先出现的大于后出现的则直接交换
            //如果两条数据时间完全相同则不交换
            if (y1 > y2)
            {
                Swap(current);
            }
            else if (y1 == y2)
            {
                if (mo1 > mo2)
                {
                    Swap(current);
                }
                else if (mo1 == mo2)
                {
                    if (d1 > d2)
                    {
                        Swap(current);
                    }
                    if (d1 == d2)
                    {
                        if (h1 > h2)
                        {
                            Swap(current);
                        }
                        else if (h1 == h2)
                        {
                            if (mi1 > mi2)
                            {
                                Swap(current);
                            }
                            else
                            {
                                ;
                            }
                        }

                    }
                }
            }
            current = current->next;
        }
    }
    current = pHead;

    return pHead;
}

void DeleteHomework(int n)
{
    Nodehw* Head = HomeworkArrange(HomeworkFetch());
    Nodehw* current = Head;
    if(n == 1)
    {
        Head = Head->next;
    }
    else if(n > 1)
    {
        int i = 0;
        while(current)
        {
            i++;
            if(i == n-1)
            {
                if(current->next)
                {
                    current->next = current->next->next;
                    qDebug()<<"删除成功";
                }
            }
            current = current->next;
        }
    }

    QFile file(Filenamehw);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open hwfile";
    }
    QDataStream fin(&file);
    current = Head;
    while(current)
    {
        fin<<current->val;
        current = current->next;
    }
    file.close();

}

