#include "Remind.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>

//------------------------------运算符重载部分------------------------------
QDataStream& operator <<(QDataStream &out,Remind &add)//输出新增
{
    out << add.GetOrganizer()<<add.GetAcContent()<<add.GetYear()<<add.GetMonth()<<add.GetDate()
        <<add.GetHour()<<add.GetMin();
    return out;
}

QDataStream& operator >>(QDataStream &in,Remind &n)//读入数据
{
    in >> n.organizer_>>n.accontent_>>n.year_>>n.month_>>n.date_>>n.hour_>>n.min_;
    return in;
}

QDataStream& operator <<(QDataStream &out,Noderm* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Noderm* &n)
{
    in >> n->val;
    return in;
}

//----------------------接口部分----------------------
void Remind::SetOrganizer(QString orginazer)
{
    organizer_ = orginazer;
}

void Remind::SetAcConnent(QString accontent)
{
    accontent_ = accontent;
}

void Remind::SetYear(int year)
{
    year_ = year;
}

void Remind::SetMonth(int month)
{
    month_ = month;
}

void Remind::SetDate(int date)
{
    date_ = date;
}

void Remind::SetHour(int hour)
{
    hour_ = hour;
}

void Remind::SetMin(int min)
{
    min_ = min;
}

int Remind::GetYear()
{
    return year_;
}

int Remind::GetMonth()
{
    return month_;
}

int Remind::GetDate()
{
    return date_;
}

int Remind::GetHour()
{
    return hour_;
}

int Remind::GetMin()
{
    return min_;
}

QString Remind::GetOrganizer()
{
    return organizer_;
}

QString Remind::GetAcContent()
{
    return accontent_;
}

bool Remind::GetMumber()
{
    if(this)
    {
        return 1;
    }
}

//--------------------------service------------------------


void SaveRemind(Noderm* pNew)
{


    qDebug()<<"Enter!!!";
    //pNew是给入的暂时链表的头结点

    //几个基本步骤：
    //1.将指针指向临时存储的链表的最后一个
    //2.得到数据文件中存储的数据
    //3.将两个链表进行拼接

    //步骤2.得到数据文件中存储的数据
    //    QDataStream finout(&file);
    Noderm* pointer = NULL;
    Noderm* pHead = NULL;
    //准备读取数据文件中的头结点
    Noderm* Each = new Noderm;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    QFile file(Filenamerm);
    file.open(QFile::ReadOnly);
    QDataStream fout(&file);
    if(fout.atEnd())
    {
        //qDebug()<<"Nothing";
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
        Each = new Noderm;
        Each->next = NULL;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    delete Each;
    //qDebug()<<"The pHead in file";


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
        //qDebug()<<"共有"<<range<<"组数据进入";
    }
    else if (!pNew)
    {//如果这个头结点并不存在
        qDebug() << "Error:链表为空" << Qt::endl;
            return ;//因为是一个void函数，所以return后面并没有参数
    }
    qDebug()<<"Here is the new list";



    //步骤三。将两个链表进行拼接
    //qDebug()<<"Did it have";

    pointer->next= pHead;
    //qDebug()<<"Finish";

    //qDebug()<<"Here";
    Noderm* Np = pNew;
    //qDebug()<<"The list prepare to be saved";
    file.close();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    //截断，因为我们要从头开始写
    {
        //qDebug() << "Error2:文件打开错误！！！" << Qt::endl;
    }
    QDataStream fin(&file);
    i = 1;
    while (Np)
    {
        //qDebug()<<"Here 2:write";
        fin<<Np;
        Np = Np->next;
        i++;
    }
    file.close();
    qDebug() << "成功保存!!!" << Qt::endl;
}

Noderm* RemindFetch(void)
{

    QFile file(Filenamerm);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"fail to open remind file ";
    }
    QDataStream fout(&file);

    if (fout.atEnd())//防止用户初次使用时文件为空导致返回空指针
    {
        QString organizer = "Vkun_s";
        QString accontent = "v Vkun_s 50";
        int year = 9999;
        int month = 9;
        int date = 9;
        int hour = 9;
        int min = 9;
        Remind* Initial = new Remind(organizer, accontent, year, month, date, hour, min);
        Noderm* Initialnode = new Noderm;
        Initialnode->val = *Initial;
        Initialnode->next = NULL;
        return Initialnode;
    }

    Noderm* pHead = NULL;
    //准备读取数据文件中的头结点
    Noderm* Each = new Noderm;
    Each->next = NULL;
    //先在这里声明一个结点

    int i = 0;
    Noderm* pointer = NULL;
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
        Each = new Noderm;
        Each->next = NULL;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    qDebug()<<"Fetch finished(remind)";
    delete Each;
    return pHead;

}

void Remind::QDBUG()
{
    qDebug()<<this->organizer_;
}

Noderm* RemindArrange(Noderm* pHead)
{
    //创建辅助指针
    Noderm* current = pHead;//此时current即为头指针，指向第一个节点
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

void Swap(Noderm* current)
{
    Remind Tem = current->val;
    Remind Tem2 = current->next->val;
    current->val = Tem2;
    current->next->val = Tem;
}

void DeleteRemind(int n)
{
    Noderm* Head = RemindArrange(RemindFetch());
    Noderm* current = Head;
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
                    //qDebug()<<"删除成功";
                }
            }
            current = current->next;
        }
    }

    QFile file(Filenamerm);
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
