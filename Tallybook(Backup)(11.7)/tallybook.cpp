#include "tallybook.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>


//链表进入文件准则：头插法进入，尾插法输出
void BillClear()
{
    QFile file(Filename1);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    file.close();
}

QDataStream& operator >>(QDataStream &in,Bill &t)
{

    in>>t.case_>>t.value_>>t.year_>>t.month_>>t.date_>>t.note_;
    return in;
}
//这个输入是确确实实地把数据对应到了每一个成员当中去

QDataStream& operator <<(QDataStream &out,Bill &t)
{
    out<<t.case_<<t.value_<<t.year_<<t.month_<<t.date_<<t.note_;
    return out;
}

QDataStream& operator <<(QDataStream &out,Node1* &t)
{
    out<<t->value;
    return out;
}

QDataStream& operator >>(QDataStream &out,Node1* &t)
{
    out>>t->value;
    return out;
}

//判断是否为闰年的函数
bool IsRun(int year) {
    if (year % 4 == 0 && year % 100) {
        return 1;
    }
    else if (year % 400 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

//根据输入的年份，月份返回日期数
int ReturnDay(int year, int month) {
    int array[]{ 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && IsRun(year)) {
        return 29;
    }
    else {
        return array[month];
    }
}

int Bill::GetYear()
{
    return year_;
}

//获得月
int Bill::GetMonth()
{
    return month_;
}

//获得日
int Bill::GetDate()
{
    return date_;
}

//获得小时
//int Bill::GetHour()
//{
//    return hour_;
//}

//获得分钟
//int Bill::GetMin()
//{
//    return min_;
//}

int Bill::GetValue()
{
    return value_;
}

int Bill::GetCase()
{
    return case_;
}

QString Bill::GetNote()
{
    return note_;
}

void Bill::SetYear(int year)
{
    year_ = year;
}
void Bill::SetMonth(int month)
{
    month_ = month;
}
void Bill::SetDate(int date)
{
    date_ = date;
}
//void Bill::SetHour(int hour)
//{
//    hour_ = hour;
//}
//void Bill::SetMin(int min)
//{
//    min_ = min;
//}
void Bill::SetValue(int value)
{
    value_ = value;
}
void Bill::SetCase(int Case)
{
    case_ = Case;
}
void Bill::SetNote(QString note)
{
    note_ = note;
}

//调试用，将这一个成员的值进行显示
void Bill::ShowRecord(void)
{
    qDebug() << year_ << "-" << month_ << "-" << date_ << " "
        ;



    if (case_ == Outlay)
    {
        qDebug() << Qt::endl << "支出" << value_ << "元";
    }
    else if (case_ == Income)
    {
        qDebug() << Qt::endl << "收入" << value_ << "元";
    }

    qDebug() << "\t备注：" << note_ << Qt::endl;
}
////如何打出好看的格式
////1. 00如何完整打出来
////2. \t的应用...我不会，啊啊啊啊啊啊

//记账本主菜单选择界面——命令行版本
void TallyBook(void)
{
    qDebug() << "欢迎来到记账本界面！！！" << Qt::endl;
    qDebug() << "1.添加账单" << Qt::endl;//Finished
    qDebug() << "2.删改账单" << Qt::endl;//Finished
    qDebug() << "3.统计账单" << Qt::endl;
    qDebug() << "4.退出账单" << Qt::endl<<Qt::endl;//Finished
    qDebug() << "请选择您需要的功能：";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        qDebug() << "Choice 1"<<Qt::endl;
    //    BillAdd();
        TallyBook();
    case 2:
        qDebug() << "Choice 2"<<Qt::endl;
     //   BillModify();
        TallyBook();
    case 3:
        qDebug() << "Choice 3"<<Qt::endl;
    //    BillStatistics();
        TallyBook();
    case 4:
        qDebug() << "Choice 4"<<Qt::endl;
        qDebug() << "感谢使用" << Qt::endl;
    //    BillQuit();
    }
}


//将目前临时存储的账单全部显示出来，仅作工具用
void ShowList1(Node1* pHead)
{
    if (pHead)
    {
        Node1* pointer = pHead;
        int range=1;
        while (pointer)
        {
            qDebug() << "记录" << range << ":";
            pointer->value.ShowRecord();
            pointer = pointer->pNext;
            range++;
        }
        qDebug()<< ("暂时存储链表如上！") << Qt::endl;
    }
    else if (!pHead)
    {
        qDebug()<<("Error:链表为空")<< Qt::endl;
    }
//    system("pause");
}

//void linkedlist<T>::outputall()
//{
//    node<T> *p = head;
//    int count = 1;
//    FILE *fp;
//    fp=fopen("data.txt","w");
//    while (p != NULL)
//    {
//        fprintf(fp, "%d\t", count);
//        count++;
//        p->data.tofile(fp); //传给tofile那边一个已经打开的可以写的文件指针，让他那边输出data的具体内容
//        //tofile()这个函数是类里面必须自己设计好的
//        p = p->next;
//    }
//    fprintf(fp, "9999\n"); //这是结束的标志，方便下一次读入文件
//    //——ps：无论database中是否有这个9999，只要最后点击相关的按钮，就会有这个9999（其实没有也没关系好像
//    qDebug()<<("调用了outputall函数");
//    fclose(fp);
//}

void SaveList1(Node1* pNew)
{


    qDebug()<<"Enter!!!";
    //pNew是给入的暂时链表的头结点

    //几个基本步骤：
    //1.将指针指向临时存储的链表的最后一个
    //2.得到数据文件中存储的数据
    //3.将两个链表进行拼接




    //步骤2.得到数据文件中存储的数据
//    QDataStream finout(&file);
    Node1* pointer = NULL;
    Node1* pHead = NULL;
    //准备读取数据文件中的头结点
    Node1* Each = new Node1;
    //先在这里声明一个结点


    int i = 0;
    QFile file(Filename1);
    file.open(QFile::ReadOnly);
    QDataStream fout(&file);
    if(fout.atEnd())    qDebug()<<"Nothing";
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
            pointer->pNext = Each;
            pointer = Each;
        }//千万注意这里要用尾插法取出！！！
        i++;
        Each = new Node1;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    qDebug()<<"The pHead in file";
    ShowList1(pHead);

    //步骤1.将指针指向临时存储的链表的最后一个

    //刚开始的时候必须要将Node分配到NULL，否则它随便指到一个内存，那就完蛋啦
    //将pointer指向临时链表的最后结点,并且得到临时链表中的总个数range
    if (pNew)
    {//如果传进来的临时链表的头结点存在
        pointer = pNew;
        int range = 0;
        while (pointer->pNext)
        {
            range++;
            pointer = pointer->pNext;
        }
        qDebug()<<"共有"<<range<<"组数据进入";
    }
    else if (!pNew)
    {//如果这个头结点并不存在
        qDebug() << "Error:链表为空" << Qt::endl;
            return ;//因为是一个void函数，所以return后面并没有参数
    }
    qDebug()<<"Here is the new list";
    ShowList1(pNew);


    //步骤三。将两个链表进行拼接
    qDebug()<<"Did it have";
    ShowList1(pointer);
    pointer->pNext= pHead;
    qDebug()<<"Finish";

    qDebug()<<"Here";
    Node1* Np = pNew;
    qDebug()<<"The list prepare to be saved";
    ShowList1(Np);
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
        Np = Np->pNext;
        i++;
    }

    qDebug() << "成功保存!!!" << Qt::endl;
};

void BillAdd(int value, int year, int month, int date,
             QString note, bool Case)
{

        Node1* Add = new Node1;
        Add->value = Bill(value, year, month, date, note, Case);
        Add->pNext = NULL;

    SaveList1(Add);
    //将临时存储表进行添加
}

void BillAdd(Bill n)
{
    Node1* Add = new Node1;
    Add->value = n;
    Add->pNext = NULL;

    SaveList1(Add);
    //将临时存储表进行添加
}


////显示所有从数据文件中拿出的账单
//void BillShow(void)
//{
//    ShowList1(BillArrange(BillFetch()));
//}

Node1* BillFetch(void)
{

    QFile file(Filename1);
    file.open(QIODevice::ReadOnly);
    QDataStream fout(&file);
    if (!fout.atEnd())
    {
        qDebug() << "fout open error!!!" << Qt::endl;
    }

    Node1* pHead = NULL;
    //准备读取数据文件中的头结点
    Node1* Each = new Node1;
    //先在这里声明一个结点

    int i = 0;
    Node1* pointer=NULL;
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
            pointer->pNext = Each;
            pointer = Each;
        }//千万注意这里要用尾插法取出！！！
        i++;
        Each = new Node1;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    return pHead;
    qDebug()<<"Fetch finished";
}

//Here is the key point！！！

//Here is the key point！！！


//Here is the key point！！！


//void BillQuit(void)
//{
//    exit(0);
//}

//void BillReplace(Node1* pHead)
//{

//    QFile file(Filename1);
//    QDataStream fout(&file);
//    if (!fout.atEnd())
//    {
//        qDebug() << "Error1:文件打开错误!!!" << Qt::endl;
//    }//这里就只是输出，所以用的是ofstream

//    Node1* pointer = pHead;
//    while (pointer)
//    {
//        fout>>pHead;
//        pointer= pointer->pNext;
//    }

//    qDebug() <<Qt::endl<< "操作成功!!" << Qt::endl;
//}

//void BillDelete(void)
//{
//    system("cls");
//    //BillShow();
//    qDebug() << "输入删除的账单序号" << Qt::endl;
//    int num;
//    std::cin >> num;
//    Node1* get = BillFetch();
//    Node1* pointer = get;

//    int cnt = 1;
//    while (pointer)
//    {
//        if (num == 1)
//        {
//            get = get->pNext;
//            break;
//        }
//        if (cnt==num-1)
//        {
//            pointer->pNext = pointer->pNext->pNext;
//            break;
//        }
//        pointer = pointer->pNext;
//        cnt++;
//    }

//    BillReplace(get);
//re6:
//    qDebug() << Qt::endl << "是否还要删除？" << Qt::endl;
//    qDebug() << "1.继续删除" << Qt::endl;
//    qDebug() << "0.退出删除" << Qt::endl;
//    qDebug() << "你的选择：";
//    int c;
//    std::cin >> c;
//    if (c != 1 && c != 0) {
//        qDebug() << "Error:输入类型错误" << Qt::endl;
//        goto re6;
//    }

//    bool choice;
//    choice = c;
//    if (choice)
//    {
//        BillDelete();
//    }
//    else
//    {
//        TallyBook();
//    }
//}

//void BillModify(void)
//{
//    qDebug() << "0.删除账单" << Qt::endl << "1.修改账单" << Qt::endl;
//    qDebug() << "输入功能：" << Qt::endl;
//    bool choice;
//    std::cin >> choice;
//    if (!choice)
//    {
//        BillDelete();
//    }
//    else
//    {
//        BillChange();
//    };
//}

//void BillChange(void)
//{
//    system("cls");
//    //BillShow();

//    qDebug() << "输入调整的账单序号" << Qt::endl;
//    int num;//要进行调整的序号
//    std::cin >> num;

//    int value, year, month, date, hour, min;
//    bool Case;
//    QString note;

//    Node1* pHead = NULL;
//    qDebug() << "请根据提示输入修改后的数据" << Qt::endl;

//    qDebug() << "输入记录时间：" << Qt::endl;
//    qDebug() << "例子：2023 10 10 12 00" << Qt::endl << "表示在2023年10月10月12：00的账单记录" << Qt::endl;
//    //这里加很多个确定时间无误的函数
//    std::cin >> year >> month >> date >> hour >> min;
//    if (year < 2000 || year>2023)
//    {
//        qDebug() << "Warning:年份错误" << Qt::endl << "Continue..." << Qt::endl;
//    }
//    if (month < 1 || month>12)
//    {
//        qDebug() << "Warning:月份错误" << Qt::endl << "Continue..." << Qt::endl;
//    }
//    //这里要用到ReturnDay();
//    if (hour < 0 || hour>24 || min < 0 || min>60)
//    {
//        qDebug() << "Warning:时间错误" << Qt::endl << "Continue..." << Qt::endl;
//    }

//    qDebug() << "输入账单类型（收入为1，支出为0）" << Qt::endl;
//re2:
//    int tem;
//    std::cin >> tem;
//    if (tem != 0 && tem != 1) {
//        qDebug() << "Error:输入类型错误！！！请重新输入！！！" << Qt::endl;
//        std::cin.clear();
//        goto re2;
//    }
//    else {
//        std::cin >> Case;
//        if (Case == Income)
//        {
//            qDebug() << "收入金额：" << Qt::endl;
//        }
//        else if (Case == Outlay)
//        {
//            qDebug() << "支出金额：" << Qt::endl;
//        }
//    }

//    std::cin >> value;

//    qDebug() << "添加备注：" << Qt::endl;
////            std::cin >> note;

//    Bill New(value, year, month, date, note, Case);
//    int cnt = 1;
//    Node1* get = BillFetch();
//    Node1* pointer = get;
//    while (pointer)
//    {
//        qDebug() << cnt << Qt::endl;
//        if (cnt == num)
//        {
//            qDebug() << "Found" << Qt::endl;
//            pointer->value = New;//不知道为什么这里不可以直接用=Bill(......)，就像在BillAdd里面一样
//            qDebug()<<"Changed"<<Qt::endl;
//            break;
//        }//遍历并且找到那个数据，只是进行数据上更改，指针并不进行更改
//        pointer = pointer->pNext;
//        cnt++;
//    }

//    BillReplace(get);

//    qDebug() << Qt::endl << "还要调整？" << Qt::endl;
//    qDebug() << "1.继续修改" << Qt::endl << "0.退出"<<Qt::endl;
//    qDebug() <<	"你的选择：";
//    bool choice;
//    std::cin >> choice;
//    if (choice)
//    {
//        BillChange();
//    }
//    else
//    {
//        TallyBook();
//    }
//}

//void Swap(Node1* current)
//{
//    Bill Tem = current->value;
//    Bill Tem2 = current->pNext->value;
//    current->value = Tem2;
//    current->pNext->value = Tem;
//}
////将前后两个结点进行替换

//Node1* BillArrange(Node1* pHead)
//{
//    //创建辅助指针
//    Node1* current = pHead;//此时current即为头指针，指向第一个节点
//    int num = 0;
//    //用于计算共有多少个结点
//    while (current)
//    {
//        current = current->pNext;
//        num++;
//    }
//    //for循环是冒泡排序第一层，while循环是冒泡排序第二层
//    for (int i = 0; i < num - 1; i++)//冒泡思想，查找num-1次
//    {
//        current = pHead;//每次都从头开始找
//        //cout << "第" << i + 1 << "次进入循环" << endl;//测试时使用
//        while (current->pNext)
//        {
//            //获取相邻两个节点中所存储的时间数据
//            int y1 = current->value.GetYear();
//            int mo1 = current->value.GetMonth();
//            int d1 = current->value.GetDate();
//            //int h1 = current->value.GetHour();
//            //int mi1 = current->value.GetMin();
//            int h1=1;
//            int mi1=2;
//            int y2 = current->pNext->value.GetYear();
//            int mo2 = current->pNext->value.GetMonth();
//            int d2 = current->pNext->value.GetDate();
//            //int h2 = current->pNext->value.GetHour();
//            int h2=2;
//            //int mi2 = current->pNext->value.GetMin();
//            int mi2=3;
//            //冒泡排序，年份先出现的大于后出现的则直接交换
//            //如果两条数据时间完全相同则不交换
//            if (y1 > y2)
//            {
//                Swap(current);
//            }
//            else if (y1 == y2)
//            {
//                if (mo1 > mo2)
//                {
//                    Swap(current);
//                }
//                else if (mo1 == mo2)
//                {
//                    if (d1 > d2)
//                    {
//                        Swap(current);
//                    }
//                    if (d1 == d2)
//                    {
//                        if (h1 > h2)
//                        {
//                            Swap(current);
//                        }
//                        else if (h1 == h2)
//                        {
//                            if (mi1 > mi2)
//                            {
//                                Swap(current);
//                            }
//                            else
//                            {
//                                ;
//                            }
//                        }

//                    }
//                }
//            }
//            current = current->pNext;
//        }
//    }
//    current = pHead;

//    return pHead;
//}

//void BillStatistics(void) {
//    system("cls");
//    qDebug() << "欢迎来到统计界面" << Qt::endl;
//    qDebug() << "0.显示所有账单" << Qt::endl;
//    qDebug() << "1.按照年份显示账单" << Qt::endl << "2.按照月份显示账单" << Qt::endl << "3.按照日期显示账单" << Qt::endl;
//    int choice;
//    qDebug() << "输入你的选择：" << Qt::endl;
//    std::cin >> choice;
//    if (choice!=0&&choice != 1 && choice != 2 && choice != 3) {
//        qDebug() << "Error:选择错误！！！" << Qt::endl;
//        BillStatistics();
//    }

//    int year = -1, month = -1, date = -1;

//    switch (choice) {
//    case 0:
//        ShowList1(BillArrange(BillFetch()));
//        break;
//    case 1:
//        qDebug() << "输入查询年份" << Qt::endl;
//                std::cin >> year;
//        qDebug() << "Here is year" << Qt::endl;
//        ShowYear(year);
//        break;
//    case 2:
//        qDebug() << "输入查询年份" << Qt::endl;
//                std::cin >> year;
//        qDebug() << "输入查询月份" << Qt::endl;
//                        std::cin >> month;
//        qDebug() << "Here is month" << Qt::endl;
//        ShowMonth(year,month);
//        break;
//    case 3:
//        qDebug() << "输入查询年份" << Qt::endl;
//                std::cin >> year;
//        qDebug() << "输入查询月份" << Qt::endl;
//                        std::cin >> month;
//        qDebug() << "输入查询日期" << Qt::endl;
//                                std::cin >> date;
//        qDebug() << "Here is date" << Qt::endl;
//        ShowDate(year,month,date);
//        break;
//    }

//    qDebug() << Qt::endl << "是否还要进行查看？" << Qt::endl;
//    qDebug() << "1.继续查看" << Qt::endl;
//    qDebug() << "0.退出查看" << Qt::endl;
//    qDebug() << "你的选择：";
//    std::cin >> choice;
//    if (choice)
//    {
//        BillStatistics();
//    }
//    else if(choice==0)
//    {
//        TallyBook();
//    }
//    else {
//        qDebug() << "Error:选择错误！！！" << Qt::endl;
//        system("cls");
//        TallyBook();
//    }
//}

//void ShowYear(int year)
//{
//    Node1* pHead = BillFetch();
//    Node1* current = pHead;//用于读取fetch的链表
//    Node1* Yhead = new Node1;//新链表头结点,它的pNext指向第一个结点
//    Node1* pre = Yhead;//创建新链表存放该年数据
//    int income = 0;//收入
//    int expense = 0;//支出
//    int change = 0;
//    int i = 0;//计数变量，用于判断输入的年份究竟有无数据
//    //while循环中完成新链表的创建以及该年份数据条数的记录
//    while (current)
//    {
//        int y = current->value.GetYear();
//        if (y == year)
//        {
//            i++;
//            Node1* Lyear = new Node1;
//            Lyear->value = current->value;
//            pre->pNext = Lyear;
//            pre = Lyear;
//            Lyear->pNext = NULL;
//        }
//        current = current->pNext;
//    }
//    pre = Yhead;//让pre重新指回来
//    if (i)
//    {
//        while (pre->pNext)
//        {
//            if (pre->pNext->value.GetCase())
//            {
//                income += pre->pNext->value.GetValue();
//            }
//            else
//            {
//                expense -= pre->pNext->value.GetValue();
//            }
//            pre = pre->pNext;
//        }
//        change = income + expense;
//        qDebug() << "这是" << year << "您的收支明细" << Qt::endl;
//        ShowList1(BillArrange(Yhead->pNext));
//        qDebug() << year << "年，您共收入" << income << "元,"
//            << "支出" << expense << "元，" << Qt::endl;
//        if (change > 0)
//        {
//            qDebug() << "这一年，您的资产增加" << change << "元" << Qt::endl;
//        }
//        else if (change == 0)
//        {
//            qDebug() << "这一年，您的资产无变化" << Qt::endl;
//        }
//        else
//        {
//            qDebug() << "这一年，您的资产减少" << (-change) << "元" << Qt::endl;
//        }
//    }
//    else
//    {
//        qDebug() << "您没有在" << year << "年的收支记录" << Qt::endl;
//    }

//}

//void ShowMonth(int year, int month)
//{
//    Node1* pHead = BillFetch();
//    Node1* current = pHead;//用于读取fetch的链表
//    Node1* MOhead = new Node1;//新链表头结点,它的pNext指向第一个结点
//    Node1* pre = MOhead;//创建新链表存放该年数据
//    int income = 0;//收入
//    int expense = 0;//支出
//    int change = 0;
//    int i = 0;//计数变量，用于判断输入的年份究竟有无数据
//    //while循环中完成新链表的创建以及该年份数据条数的记录
//    while (current)
//    {
//        int y = current->value.GetYear();
//        if (y == year)
//        {
//            int mo = current->value.GetMonth();
//            if (mo == month)
//            {
//                i++;
//                Node1* Lmonth = new Node1;
//                Lmonth->value = current->value;
//                pre->pNext = Lmonth;
//                pre = Lmonth;
//                Lmonth->pNext = NULL;
//            }
//        }
//        current = current->pNext;
//    }
//    pre = MOhead;//让pre重新指回来
//    if (i)
//    {
//        while (pre->pNext)
//        {
//            if (pre->pNext->value.GetCase())
//            {
//                income += pre->pNext->value.GetValue();
//            }
//            else
//            {
//                expense -= pre->pNext->value.GetValue();
//            }
//            pre = pre->pNext;
//        }
//        change = income + expense;
//        qDebug() << "这是" << year << "年" << month << "月您的收支明细" << Qt::endl;
//        ShowList1(BillArrange(MOhead->pNext));
//        qDebug() << year << "年" << month << "月，您共收入" << income << "元, "
//            << "支出" << expense << "元，" << Qt::endl;
//        if (change > 0)
//        {
//            qDebug() << "这一月，您的资产增加" << change << "元" << Qt::endl;
//        }
//        else if (change == 0)
//        {
//            qDebug() << "这一月，您的资产无变化" << Qt::endl;
//        }
//        else
//        {
//            qDebug() << "这一月，您的资产减少" << (-change) << "元" << Qt::endl;
//        }
//    }
//    else
//    {
//        qDebug() << "您没有在" << year << "年" << month << "月的收支记录" << Qt::endl;
//    }

//}

//void ShowDate(int year, int month, int date)
//{
//    Node1* pHead = BillFetch();
//    Node1* current = pHead;//用于读取fetch的链表
//    Node1* Dhead = new Node1;//新链表头结点,它的pNext指向第一个结点
//    Node1* pre = Dhead;//创建新链表存放该年数据
//    int income = 0;//收入
//    int expense = 0;//支出
//    int change = 0;
//    int i = 0;//计数变量，用于判断输入的年份究竟有无数据
//    //while循环中完成新链表的创建以及该年份数据条数的记录
//    while (current)
//    {
//        int y = current->value.GetYear();
//        if (y == year)
//        {
//            int mo = current->value.GetMonth();
//            if (mo == month)
//            {
//                int d = current->value.GetDate();
//                if (d == date)
//                {
//                    i++;
//                    Node1* Lday = new Node1;
//                    Lday->value = current->value;
//                    pre->pNext = Lday;
//                    pre = Lday;
//                    Lday->pNext = NULL;
//                }
//            }
//        }
//        current = current->pNext;
//    }
//    pre = Dhead;//让pre重新指回来
//    if (i)
//    {
//        while (pre->pNext)
//        {
//            if (pre->pNext->value.GetCase())
//            {
//                income += pre->pNext->value.GetValue();
//            }
//            else
//            {
//                expense -= pre->pNext->value.GetValue();
//            }
//            pre = pre->pNext;
//        }
//        change = income + expense;
//        qDebug() << "这是" << year << "年" << month << "月" << date << "日您的收支明细" << Qt::endl;
//        ShowList1(BillArrange(Dhead->pNext));
//        qDebug() << year << "年" << month << "月" << date << "日您共收入" << income << "元, "
//            << "支出" << expense << "元，" << Qt::endl;
//        if (change > 0)
//        {
//            qDebug() << "这一天，您的资产增加" << change << "元" << Qt::endl;
//        }
//        else if (change == 0)
//        {
//            qDebug() << "这一天，您的资产无变化" << Qt::endl;
//        }
//        else
//        {
//            qDebug() << "这一天，您的资产减少" << (-change) << "元" << Qt::endl;
//        }
//    }
//    else
//    {
//        qDebug() << "您没有在" << year << "年" << month << "月" << date << "日的收支记录" << Qt::endl;
//    }

//}

//完结撒花！！！			2023.10.17（自2023.10.10始）










