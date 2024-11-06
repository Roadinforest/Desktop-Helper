#include"tallyBook.h"
//链表进入文件准则：头插法进入，尾插法输出

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
int Bill::GetHour()
{
	return hour_;
}

//获得分钟
int Bill::GetMin()
{
	return min_;
}

int Bill::GetValue()
{
	return value_;
}

int Bill::GetCase()
{
	return case_;
}

string Bill::GetNote()
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
void Bill::SetHour(int hour)
{
	hour_ = hour;
}
void Bill::SetMin(int min)
{
	min_ = min;
}
void Bill::SetValue(int value)
{
	value_ = value;
}
void Bill::SetCase(int Case)
{
	case_ = Case;
}
void Bill::SetNote(string note)
{
	note_ = note;
}

void Bill::ShowRecord(void) 
{
	cout << year_ << "-" << month_ << "-" << date_ << " "
		<< hour_ << ":";

	if (min_ == 0) cout << "00" << " ";//为了格式美观
	else cout << min_ << " ";

	if (case_ == Outlay) 
	{
		cout << endl << "支出" << value_ << "元";
	}
	else if (case_ == Income)
	{
		cout << endl << "收入" << value_ << "元";
	}

	cout << "\t备注：" << note_ << endl;
}
//如何打出好看的格式
//1. 00如何完整打出来
//2. \t的应用...我不会，啊啊啊啊啊啊

//记账本主菜单选择界面
void TallyBook(void) 
{
	system("cls");

	cout << "欢迎来到记账本界面！！！" << endl;
	cout << "1.添加账单" << endl;//Finished
	cout << "2.删改账单" << endl;//Finished
	cout << "3.统计账单" << endl;
	cout << "4.退出账单" << endl<<endl;//Finished
	cout << "请选择您需要的功能：";

	int choice;
	cin >> choice;
	
	switch (choice)
	{
	case 1:
		cout << "Choice 1"<<endl;
		BillAdd();
		TallyBook();
	case 2:
		cout << "Choice 2"<<endl;
		BillModify();
		TallyBook();
	case 3:
		cout << "Choice 3"<<endl;
		BillStatistics();
		TallyBook();
	case 4:
		cout << "Choice 4"<<endl;
		cout << "感谢使用" << endl;
		BillQuit();
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
			cout << "记录" << range << ":";
			pointer->value.ShowRecord();
			pointer = pointer->pNext;
			range++;
		}
		cout << "这是目前链表里的全部账单啦！" << endl;
	}
	else if (!pHead) 
	{
		cout << "Error:链表为空" << endl;
	}
	system("pause");
}

void SaveList1(Node1* pNew) 
{
	//pNew是给入的暂时链表的头结点

	Node1* pointer = NULL;
	//刚开始的时候必须要将Node分配到NULL，否则它随便指到一个内存，那就完蛋啦

	if (pNew)
	{//如果传进来的临时链表的头结点存在
		pointer = pNew;
		int range = 0;
		while (pointer)
		{
			range++;
			pointer = pointer->pNext;
		}
	}
	else if (!pNew) 
	{//如果这个头结点并不存在
		cout << "Error:链表为空" << endl;
	}
	//得到临时链表中的总个数range,并且将pointer指向临时链表的最后结点

	ofstream fout(Filename1, ios::binary | ios::app);
	if (!fout.is_open()) 
	{
		cout << "Error1:文件打开错误！！！" << endl;
	}
	fout.close();
	//这两步的工作是为了将文件创建（如果它一开始不存在的话）

	fstream finout(Filename1, ios::in | ios::out | ios::binary);
	if (!finout.is_open())
	{
		cout << "Error2:文件打开错误！！！" << endl;
	}//几个可能：1.并不存在这个文件 2.硬件空间不足 3.权限不足(多见于Linux)

	Node1* pHead = NULL;
	//准备读取数据文件中的头结点
	Node1* Each = new Node1;
	//先在这里声明一个结点

	int i = 0;

	while (finout.read((char*)Each, sizeof(Node1))) 
	{
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

	if(pNew)
	{	
		pointer = pNew;
	while (pointer->pNext)
	{
		pointer = pointer->pNext;
	}
	pointer->pNext = pHead;
}
	//pointer指临时链表的最后位置，pHead在这里指读取数据的链表的头结点
	//将后来链表的结尾与原本链表的开头连接起来

	Node1* Np = pNew;

	finout.clear();//将流状态恢复
	finout.seekp(ios::beg);//将文件指针指向刚开始
	//将指针指向最开始代表着我们是在进行全覆盖，而非是在原有基础上添加
	i = 1;
	while (Np) 
	{
		finout.write((const char*)Np, sizeof(Node1));
		Np = Np->pNext;
		i++;
	}

	cout << "成功保存!!!" << endl;
};

void BillAdd(void)
{
	int value, year, month, date, hour, min;
	bool Case;
	string note;
	int times;

	system("cls");

	cout << "请输入添加账单条数：" << endl;
	cin >> times;
	if (!times) 
	{ 
		cout << "Error:输入条数有误，请重新操作" << endl;
		BillAdd();
	}

	Node1* pHead=NULL;

	for (int i = 0; i < times; i++) 
	{
		system("cls");
		BillShow();
		cout << endl << "这里是，第" << i + 1 << "条记录的输入界面" << endl;
		cout << "输入记录时间：" << endl;
		cout << "例子：2023 10 10 12 00" << endl << "表示在2023年10月10月12：00的账单记录" << endl;
		//这里加很多个确定时间无误的函数
		cin >> year >> month >> date >> hour >> min;
		if (year < 2000 || year>2023) 
		{
			cout << "Warning:年份错误" << endl<<"Continue..." << endl;
		}
		if (month < 1 || month>12) 
		{
			cout<<  "Warning:月份错误" << endl<<"Continue..." << endl;
		}
		if (date<1 || date>ReturnDay(year, month)) {
			cout << "Waring:日期错误" << endl << "Continue..." << endl;
		}
		if (hour < 0 || hour>24||min<0||min>60)
		{
			cout << "Warning:时间错误" << endl << "Continue..." << endl;
		}

re1:
		cout << "确定账单类型（收入为1，支出为0）" << endl;
		int tem;
		cin >> tem;
		if (tem!=0&&tem!=1) {
			cout << "Error:输入类型错误！！！请重新输入！！！" << endl;
			cin.clear();
			goto re1;
		}
		//先用int量输入，输入之后先进行检查，再降级输入到bool量里头
		//直接检查bool量，会出错...
		else {
			Case = tem;
			if (Case == Income)
			{
				cout << "收入金额：" << endl;
			}
			else if (Case == Outlay)
			{
				cout << "支出金额：" << endl;
			}
		}
		cin >> value;
		cout << "添加备注：" << endl;
		cin >> note;

		Node1* Add = new Node1;
		Add->value = Bill(value, year, month, date, hour, min, note, Case);
		Add->pNext = NULL;

		if (i == 0)
		{
			pHead = Add;
		}
		else if (i > 0)
		{
			Add->pNext = pHead;
			pHead= Add;
		}
		//进行头插法
	}

	SaveList1(pHead);
	//将临时存储表进行添加

	system("cls");
	cout << "1.继续添加" << endl;
	cout << "0.退出添加" << endl;
	cout << endl << "输入选择：" << endl;
	bool choice;
	cin >> choice;

	if (choice)
	{
		BillAdd();
	}
	else
	{
		TallyBook();
	}

}

//显示所有从数据文件中拿出的账单
void BillShow(void)
{
	ShowList1(BillArrange(BillFectch()));
}

Node1* BillFectch(void)
{

	ofstream fout(Filename1, ios::binary | ios::app);
	if (!fout.is_open())
	{
		cout << "fout open error!!!" << endl;
	}
	fout.close();

	fstream finout(Filename1, ios::in | ios::out | ios::binary);
	if (!finout.is_open())
	{
		cout << "finout open error!!!" << endl;
	}//几个可能：1.并不存在这个文件 2.硬件空间不足 3.权限不足(多见于Linux)

	Node1* pHead = NULL;
	//准备读取数据文件中的头结点
	Node1* Each = new Node1;
	//先在这里声明一个结点

	int i = 0;
	Node1* pointer=NULL;
	while (finout.read((char*)Each, sizeof(Node1)))
	{
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
	system("pause");
}

void BillQuit(void) 
{
	exit(0);
}

void BillReplace(Node1* pHead)
{
	ofstream fout(Filename1, ios::binary );
	if (!fout.is_open()) 
	{
		cout << "Error1:文件打开错误!!!" << endl;
	}//这里就只是输出，所以用的是ofstream
	
	Node1* pointer = pHead;
	while (pointer) 
	{
		fout.write((const char*)pointer, sizeof(Node1));
		pointer= pointer->pNext;
	}

	cout <<endl<< "操作成功!!" << endl;
}

void BillDelete(void)
{
	system("cls");
	BillShow();
	cout << "输入删除的账单序号" << endl;
	int num;
	cin >> num;
	Node1* get = BillFectch();
	Node1* pointer = get;

	int cnt = 1;
	while (pointer) 
	{
		if (num == 1)
		{
			get = get->pNext;
			break;
		}
		if (cnt==num-1)
		{
			pointer->pNext = pointer->pNext->pNext;
			break;
		}
		pointer = pointer->pNext;
		cnt++;
	}

	BillReplace(get);

	cout << endl << "是否还要删除？" << endl;
	cout << "1.继续删除" << endl;
	cout << "0.退出删除" << endl;
	cout << "你的选择：";
	bool choice;
	cin >> choice;
	if (choice) 
	{
		BillDelete();
	}
	else 
	{
		TallyBook();
	}
}

void BillModify(void)
{
	cout << "0.删除账单" << endl << "1.修改账单" << endl;
	cout << "输入功能：" << endl;
	bool choice;
	cin >> choice;
	if (!choice)
	{ 
		BillDelete(); 
	}
	else 
	{ 
		BillChange();
	};
}

void BillChange(void) 
{
	system("cls");
	BillShow();

	cout << "输入调整的账单序号" << endl;
	int num;//要进行调整的序号
	cin >> num;

	int value, year, month, date, hour, min;
	bool Case;
	string note;

	Node1* pHead = NULL;
	cout << "请根据提示输入修改后的数据" << endl;

	cout << "输入记录时间：" << endl;
	cout << "例子：2023 10 10 12 00" << endl << "表示在2023年10月10月12：00的账单记录" << endl;
	//这里加很多个确定时间无误的函数
	cin >> year >> month >> date >> hour >> min;
	if (year < 2000 || year>2023)
	{
		cout << "Warning:年份错误" << endl << "Continue..." << endl;
	}
	if (month < 1 || month>12)
	{
		cout << "Warning:月份错误" << endl << "Continue..." << endl;
	}
	//这里要用到ReturnDay();
	if (hour < 0 || hour>24 || min < 0 || min>60)
	{
		cout << "Warning:时间错误" << endl << "Continue..." << endl;
	}

	cout << "输入账单类型（收入为1，支出为0）" << endl;
re2:
	int tem;
	cin >> tem;
	if (tem != 0 && tem != 1) {
		cout << "Error:输入类型错误！！！请重新输入！！！" << endl;
		cin.clear();
		goto re2;
	}
	else {
		cin >> Case;
		if (Case == Income)
		{
			cout << "收入金额：" << endl;
		}
		else if (Case == Outlay)
		{
			cout << "支出金额：" << endl;
		}
	}

	cin >> value;

	cout << "添加备注：" << endl;
	cin >> note;

	Bill New(value, year, month, date, hour, min, note, Case);
	int cnt = 1;
	Node1* get = BillFectch();
	Node1* pointer = get;
	while (pointer)
	{
		cout << cnt << endl;
		if (cnt == num) 
		{
			cout << "Found" << endl;
			pointer->value = New;//不知道为什么这里不可以直接用=Bill(......)，就像在BillAdd里面一样
			cout<<"Changed"<<endl;
			break;
		}//遍历并且找到那个数据，只是进行数据上更改，指针并不进行更改
		pointer = pointer->pNext;
		cnt++;
	}
	
	BillReplace(get);

	cout << endl << "还要调整？" << endl;
	cout << "1.继续修改" << endl << "0.退出"<<endl;
	cout <<	"你的选择：";
	bool choice;
	cin >> choice;
	if (choice) 
	{
		BillChange();
	}
	else 
	{
		TallyBook();
	}
}

void Swap(Node1* current) 
{
	Bill Tem = current->value;
	Bill Tem2 = current->pNext->value;
	current->value = Tem2;
	current->pNext->value = Tem;
}
//将前后两个结点进行替换

Node1* BillArrange(Node1* pHead)
{
	//创建辅助指针
	Node1* current = pHead;//此时current即为头指针，指向第一个节点
	int num = 0;
	//用于计算共有多少个结点
	while (current)
	{
		current = current->pNext;
		num++;
	}
	//for循环是冒泡排序第一层，while循环是冒泡排序第二层
	for (int i = 0; i < num - 1; i++)//冒泡思想，查找num-1次
	{
		current = pHead;//每次都从头开始找
		//cout << "第" << i + 1 << "次进入循环" << endl;//测试时使用
		while (current->pNext)
		{
			//获取相邻两个节点中所存储的时间数据
			int y1 = current->value.GetYear();
			int mo1 = current->value.GetMonth();
			int d1 = current->value.GetDate();
			int h1 = current->value.GetHour();
			int mi1 = current->value.GetMin();
			int y2 = current->pNext->value.GetYear();
			int mo2 = current->pNext->value.GetMonth();
			int d2 = current->pNext->value.GetDate();
			int h2 = current->pNext->value.GetHour();
			int mi2 = current->pNext->value.GetMin();
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
			current = current->pNext;
		}
	}
	current = pHead;

	return pHead;
}

void BillStatistics(void) {
	system("cls");
	cout << "欢迎来到统计界面" << endl;
	cout << "0.显示所有账单" << endl;
	cout << "1.按照年份显示账单" << endl << "2.按照月份显示账单" << endl << "3.按照日期显示账单" << endl;
	int choice;
	cout << "输入你的选择：" << endl;
	cin >> choice;
	if (choice!=0&&choice != 1 && choice != 2 && choice != 3) {
		cout << "Error:选择错误！！！" << endl;
		BillStatistics();
	}

	int year = -1, month = -1, date = -1;

	switch (choice) {
	case 0:
		ShowList1(BillArrange(BillFectch()));
		break;
	case 1:
		cout << "输入查询年份" << endl;
		cin >> year;
		cout << "Here is year" << endl;
		ShowYear(year);
		break;
	case 2:
		cout << "输入查询年份" << endl;
		cin >> year;
		cout << "输入查询月份" << endl;
		cin >> month;
		cout << "Here is month" << endl;
		ShowMonth(year,month);
		break;
	case 3:
		cout << "输入查询年份" << endl;
		cin >> year;
		cout << "输入查询月份" << endl;
		cin >> month;
		cout << "输入查询日期" << endl;
		cin >> date;
		cout << "Here is date" << endl;
		ShowDate(year,month,date);
		break;
	}

	cout << endl << "是否还要进行查看？" << endl;
	cout << "1.继续查看" << endl;
	cout << "0.退出查看" << endl;
	cout << "你的选择：";
	cin >> choice;
	if (choice)
	{
		BillStatistics();
	}
	else if(choice==0)
	{
		TallyBook();
	}
	else {
		cout << "Error:选择错误！！！" << endl;
		system("cls");
		TallyBook();
	}
}

void ShowYear(int year)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//用于读取fetch的链表
	Node1* Yhead = new Node1;//新链表头结点,它的pNext指向第一个结点
	Node1* pre = Yhead;//创建新链表存放该年数据
	int income = 0;//收入
	int expense = 0;//支出
	int change = 0;
	int i = 0;//计数变量，用于判断输入的年份究竟有无数据
	//while循环中完成新链表的创建以及该年份数据条数的记录
	while (current)
	{
		int y = current->value.GetYear();
		if (y == year)
		{
			i++;
			Node1* Lyear = new Node1;
			Lyear->value = current->value;
			pre->pNext = Lyear;
			pre = Lyear;
			Lyear->pNext = NULL;
		}
		current = current->pNext;
	}
	pre = Yhead;//让pre重新指回来
	if (i)
	{
		while (pre->pNext)
		{
			if (pre->pNext->value.GetCase())
			{
				income += pre->pNext->value.GetValue();
			}
			else
			{
				expense -= pre->pNext->value.GetValue();
			}
			pre = pre->pNext;
		}
		change = income + expense;
		cout << "这是" << year << "您的收支明细" << endl;
		ShowList1(BillArrange(Yhead->pNext));
		cout << year << "年，您共收入" << income << "元,"
			<< "支出" << expense << "元，" << endl;
		if (change > 0)
		{
			cout << "这一年，您的资产增加" << change << "元" << endl;
		}
		else if (change == 0)
		{
			cout << "这一年，您的资产无变化" << endl;
		}
		else
		{
			cout << "这一年，您的资产减少" << (-change) << "元" << endl;
		}
	}
	else
	{
		cout << "您没有在" << year << "年的收支记录" << endl;
	}

}

void ShowMonth(int year, int month)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//用于读取fetch的链表
	Node1* MOhead = new Node1;//新链表头结点,它的pNext指向第一个结点
	Node1* pre = MOhead;//创建新链表存放该年数据
	int income = 0;//收入
	int expense = 0;//支出
	int change = 0;
	int i = 0;//计数变量，用于判断输入的年份究竟有无数据
	//while循环中完成新链表的创建以及该年份数据条数的记录
	while (current)
	{
		int y = current->value.GetYear();
		if (y == year)
		{
			int mo = current->value.GetMonth();
			if (mo == month)
			{
				i++;
				Node1* Lmonth = new Node1;
				Lmonth->value = current->value;
				pre->pNext = Lmonth;
				pre = Lmonth;
				Lmonth->pNext = NULL;
			}
		}
		current = current->pNext;
	}
	pre = MOhead;//让pre重新指回来
	if (i)
	{
		while (pre->pNext)
		{
			if (pre->pNext->value.GetCase())
			{
				income += pre->pNext->value.GetValue();
			}
			else
			{
				expense -= pre->pNext->value.GetValue();
			}
			pre = pre->pNext;
		}
		change = income + expense;
		cout << "这是" << year << "年" << month << "月您的收支明细" << endl;
		ShowList1(BillArrange(MOhead->pNext));
		cout << year << "年" << month << "月，您共收入" << income << "元, "
			<< "支出" << expense << "元，" << endl;
		if (change > 0)
		{
			cout << "这一月，您的资产增加" << change << "元" << endl;
		}
		else if (change == 0)
		{
			cout << "这一月，您的资产无变化" << endl;
		}
		else
		{
			cout << "这一月，您的资产减少" << (-change) << "元" << endl;
		}
	}
	else
	{
		cout << "您没有在" << year << "年" << month << "月的收支记录" << endl;
	}

}

void ShowDate(int year, int month, int date)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//用于读取fetch的链表
	Node1* Dhead = new Node1;//新链表头结点,它的pNext指向第一个结点
	Node1* pre = Dhead;//创建新链表存放该年数据
	int income = 0;//收入
	int expense = 0;//支出
	int change = 0;
	int i = 0;//计数变量，用于判断输入的年份究竟有无数据
	//while循环中完成新链表的创建以及该年份数据条数的记录
	while (current)
	{
		int y = current->value.GetYear();
		if (y == year)
		{
			int mo = current->value.GetMonth();
			if (mo == month)
			{
				int d = current->value.GetDate();
				if (d == date)
				{
					i++;
					Node1* Lday = new Node1;
					Lday->value = current->value;
					pre->pNext = Lday;
					pre = Lday;
					Lday->pNext = NULL;
				}
			}
		}
		current = current->pNext;
	}
	pre = Dhead;//让pre重新指回来
	if (i)
	{
		while (pre->pNext)
		{
			if (pre->pNext->value.GetCase())
			{
				income += pre->pNext->value.GetValue();
			}
			else
			{
				expense -= pre->pNext->value.GetValue();
			}
			pre = pre->pNext;
		}
		change = income + expense;
		cout << "这是" << year << "年" << month << "月" << date << "日您的收支明细" << endl;
		ShowList1(BillArrange(Dhead->pNext));
		cout << year << "年" << month << "月" << date << "日您共收入" << income << "元, "
			<< "支出" << expense << "元，" << endl;
		if (change > 0)
		{
			cout << "这一天，您的资产增加" << change << "元" << endl;
		}
		else if (change == 0)
		{
			cout << "这一天，您的资产无变化" << endl;
		}
		else
		{
			cout << "这一天，您的资产减少" << (-change) << "元" << endl;
		}
	}
	else
	{
		cout << "您没有在" << year << "年" << month << "月" << date << "日的收支记录" << endl;
	}

}

//完结撒花！！！			2023.10.17（自2023.10.10始）







