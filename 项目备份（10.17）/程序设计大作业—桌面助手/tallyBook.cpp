#include"tallyBook.h"
//��������ļ�׼��ͷ�巨���룬β�巨���

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

//�����������ݣ��·ݷ���������
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

//�����
int Bill::GetMonth()
{
	return month_;
}

//�����
int Bill::GetDate()
{
	return date_;
}

//���Сʱ
int Bill::GetHour()
{
	return hour_;
}

//��÷���
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

	if (min_ == 0) cout << "00" << " ";//Ϊ�˸�ʽ����
	else cout << min_ << " ";

	if (case_ == Outlay) 
	{
		cout << endl << "֧��" << value_ << "Ԫ";
	}
	else if (case_ == Income)
	{
		cout << endl << "����" << value_ << "Ԫ";
	}

	cout << "\t��ע��" << note_ << endl;
}
//��δ���ÿ��ĸ�ʽ
//1. 00������������
//2. \t��Ӧ��...�Ҳ��ᣬ������������

//���˱����˵�ѡ�����
void TallyBook(void) 
{
	system("cls");

	cout << "��ӭ�������˱����棡����" << endl;
	cout << "1.����˵�" << endl;//Finished
	cout << "2.ɾ���˵�" << endl;//Finished
	cout << "3.ͳ���˵�" << endl;
	cout << "4.�˳��˵�" << endl<<endl;//Finished
	cout << "��ѡ������Ҫ�Ĺ��ܣ�";

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
		cout << "��лʹ��" << endl;
		BillQuit();
	}
}


//��Ŀǰ��ʱ�洢���˵�ȫ����ʾ����������������
void ShowList1(Node1* pHead)
{
	if (pHead) 
	{
		Node1* pointer = pHead;
		int range=1;
		while (pointer)
		{
			cout << "��¼" << range << ":";
			pointer->value.ShowRecord();
			pointer = pointer->pNext;
			range++;
		}
		cout << "����Ŀǰ�������ȫ���˵�����" << endl;
	}
	else if (!pHead) 
	{
		cout << "Error:����Ϊ��" << endl;
	}
	system("pause");
}

void SaveList1(Node1* pNew) 
{
	//pNew�Ǹ������ʱ�����ͷ���

	Node1* pointer = NULL;
	//�տ�ʼ��ʱ�����Ҫ��Node���䵽NULL�����������ָ��һ���ڴ棬�Ǿ��군��

	if (pNew)
	{//�������������ʱ�����ͷ������
		pointer = pNew;
		int range = 0;
		while (pointer)
		{
			range++;
			pointer = pointer->pNext;
		}
	}
	else if (!pNew) 
	{//������ͷ��㲢������
		cout << "Error:����Ϊ��" << endl;
	}
	//�õ���ʱ�����е��ܸ���range,���ҽ�pointerָ����ʱ����������

	ofstream fout(Filename1, ios::binary | ios::app);
	if (!fout.is_open()) 
	{
		cout << "Error1:�ļ��򿪴��󣡣���" << endl;
	}
	fout.close();
	//�������Ĺ�����Ϊ�˽��ļ������������һ��ʼ�����ڵĻ���

	fstream finout(Filename1, ios::in | ios::out | ios::binary);
	if (!finout.is_open())
	{
		cout << "Error2:�ļ��򿪴��󣡣���" << endl;
	}//�������ܣ�1.������������ļ� 2.Ӳ���ռ䲻�� 3.Ȩ�޲���(�����Linux)

	Node1* pHead = NULL;
	//׼����ȡ�����ļ��е�ͷ���
	Node1* Each = new Node1;
	//������������һ�����

	int i = 0;

	while (finout.read((char*)Each, sizeof(Node1))) 
	{
		//ÿһ����㣬ֻ�иտ�ʼ��ʱ��������䶯̬�ڴ棬֮�������еط����Դ�
		if (i == 0)
		{
			pHead = Each;//��pHead���г�ʼ��
			pointer = pHead;
		}
		else if (i > 0) 
		{
			pointer->pNext = Each;
			pointer = Each;
		}//ǧ��ע������Ҫ��β�巨ȡ��������
		i++;
		Each = new Node1;
		//ǧ��ǧ��ע��ֻ�����ڽ�β����Each���䶯̬�ڴ棬��Ϊ���ǵĸı��������while�н��е�
		//���ǽ����������ڵ�һ�У�Ҳ���ǽ��������ڶ�ȡ֮ǰ�����Ὣ�������ݱ��Ĭ��ֵ
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
	//pointerָ��ʱ��������λ�ã�pHead������ָ��ȡ���ݵ������ͷ���
	//����������Ľ�β��ԭ������Ŀ�ͷ��������

	Node1* Np = pNew;

	finout.clear();//����״̬�ָ�
	finout.seekp(ios::beg);//���ļ�ָ��ָ��տ�ʼ
	//��ָ��ָ���ʼ�������������ڽ���ȫ���ǣ���������ԭ�л��������
	i = 1;
	while (Np) 
	{
		finout.write((const char*)Np, sizeof(Node1));
		Np = Np->pNext;
		i++;
	}

	cout << "�ɹ�����!!!" << endl;
};

void BillAdd(void)
{
	int value, year, month, date, hour, min;
	bool Case;
	string note;
	int times;

	system("cls");

	cout << "����������˵�������" << endl;
	cin >> times;
	if (!times) 
	{ 
		cout << "Error:�����������������²���" << endl;
		BillAdd();
	}

	Node1* pHead=NULL;

	for (int i = 0; i < times; i++) 
	{
		system("cls");
		BillShow();
		cout << endl << "�����ǣ���" << i + 1 << "����¼���������" << endl;
		cout << "�����¼ʱ�䣺" << endl;
		cout << "���ӣ�2023 10 10 12 00" << endl << "��ʾ��2023��10��10��12��00���˵���¼" << endl;
		//����Ӻܶ��ȷ��ʱ������ĺ���
		cin >> year >> month >> date >> hour >> min;
		if (year < 2000 || year>2023) 
		{
			cout << "Warning:��ݴ���" << endl<<"Continue..." << endl;
		}
		if (month < 1 || month>12) 
		{
			cout<<  "Warning:�·ݴ���" << endl<<"Continue..." << endl;
		}
		if (date<1 || date>ReturnDay(year, month)) {
			cout << "Waring:���ڴ���" << endl << "Continue..." << endl;
		}
		if (hour < 0 || hour>24||min<0||min>60)
		{
			cout << "Warning:ʱ�����" << endl << "Continue..." << endl;
		}

re1:
		cout << "ȷ���˵����ͣ�����Ϊ1��֧��Ϊ0��" << endl;
		int tem;
		cin >> tem;
		if (tem!=0&&tem!=1) {
			cout << "Error:�������ʹ��󣡣������������룡����" << endl;
			cin.clear();
			goto re1;
		}
		//����int�����룬����֮���Ƚ��м�飬�ٽ������뵽bool����ͷ
		//ֱ�Ӽ��bool���������...
		else {
			Case = tem;
			if (Case == Income)
			{
				cout << "�����" << endl;
			}
			else if (Case == Outlay)
			{
				cout << "֧����" << endl;
			}
		}
		cin >> value;
		cout << "��ӱ�ע��" << endl;
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
		//����ͷ�巨
	}

	SaveList1(pHead);
	//����ʱ�洢��������

	system("cls");
	cout << "1.�������" << endl;
	cout << "0.�˳����" << endl;
	cout << endl << "����ѡ��" << endl;
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

//��ʾ���д������ļ����ó����˵�
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
	}//�������ܣ�1.������������ļ� 2.Ӳ���ռ䲻�� 3.Ȩ�޲���(�����Linux)

	Node1* pHead = NULL;
	//׼����ȡ�����ļ��е�ͷ���
	Node1* Each = new Node1;
	//������������һ�����

	int i = 0;
	Node1* pointer=NULL;
	while (finout.read((char*)Each, sizeof(Node1)))
	{
		//ÿһ����㣬ֻ�иտ�ʼ��ʱ��������䶯̬�ڴ棬֮�������еط����Դ�
		if (i == 0) 
		{
			pHead = Each;//��pHead���г�ʼ��
			pointer = pHead;
		}
		else if (i > 0)
		{
			pointer->pNext = Each;
			pointer = Each;
		}//ǧ��ע������Ҫ��β�巨ȡ��������
		i++;
		Each = new Node1;
		//ǧ��ǧ��ע��ֻ�����ڽ�β����Each���䶯̬�ڴ棬��Ϊ���ǵĸı��������while�н��е�
		//���ǽ����������ڵ�һ�У�Ҳ���ǽ��������ڶ�ȡ֮ǰ�����Ὣ�������ݱ��Ĭ��ֵ
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
		cout << "Error1:�ļ��򿪴���!!!" << endl;
	}//�����ֻ������������õ���ofstream
	
	Node1* pointer = pHead;
	while (pointer) 
	{
		fout.write((const char*)pointer, sizeof(Node1));
		pointer= pointer->pNext;
	}

	cout <<endl<< "�����ɹ�!!" << endl;
}

void BillDelete(void)
{
	system("cls");
	BillShow();
	cout << "����ɾ�����˵����" << endl;
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

	cout << endl << "�Ƿ�Ҫɾ����" << endl;
	cout << "1.����ɾ��" << endl;
	cout << "0.�˳�ɾ��" << endl;
	cout << "���ѡ��";
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
	cout << "0.ɾ���˵�" << endl << "1.�޸��˵�" << endl;
	cout << "���빦�ܣ�" << endl;
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

	cout << "����������˵����" << endl;
	int num;//Ҫ���е��������
	cin >> num;

	int value, year, month, date, hour, min;
	bool Case;
	string note;

	Node1* pHead = NULL;
	cout << "�������ʾ�����޸ĺ������" << endl;

	cout << "�����¼ʱ�䣺" << endl;
	cout << "���ӣ�2023 10 10 12 00" << endl << "��ʾ��2023��10��10��12��00���˵���¼" << endl;
	//����Ӻܶ��ȷ��ʱ������ĺ���
	cin >> year >> month >> date >> hour >> min;
	if (year < 2000 || year>2023)
	{
		cout << "Warning:��ݴ���" << endl << "Continue..." << endl;
	}
	if (month < 1 || month>12)
	{
		cout << "Warning:�·ݴ���" << endl << "Continue..." << endl;
	}
	//����Ҫ�õ�ReturnDay();
	if (hour < 0 || hour>24 || min < 0 || min>60)
	{
		cout << "Warning:ʱ�����" << endl << "Continue..." << endl;
	}

	cout << "�����˵����ͣ�����Ϊ1��֧��Ϊ0��" << endl;
re2:
	int tem;
	cin >> tem;
	if (tem != 0 && tem != 1) {
		cout << "Error:�������ʹ��󣡣������������룡����" << endl;
		cin.clear();
		goto re2;
	}
	else {
		cin >> Case;
		if (Case == Income)
		{
			cout << "�����" << endl;
		}
		else if (Case == Outlay)
		{
			cout << "֧����" << endl;
		}
	}

	cin >> value;

	cout << "��ӱ�ע��" << endl;
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
			pointer->value = New;//��֪��Ϊʲô���ﲻ����ֱ����=Bill(......)��������BillAdd����һ��
			cout<<"Changed"<<endl;
			break;
		}//���������ҵ��Ǹ����ݣ�ֻ�ǽ��������ϸ��ģ�ָ�벢�����и���
		pointer = pointer->pNext;
		cnt++;
	}
	
	BillReplace(get);

	cout << endl << "��Ҫ������" << endl;
	cout << "1.�����޸�" << endl << "0.�˳�"<<endl;
	cout <<	"���ѡ��";
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
//��ǰ�������������滻

Node1* BillArrange(Node1* pHead)
{
	//��������ָ��
	Node1* current = pHead;//��ʱcurrent��Ϊͷָ�룬ָ���һ���ڵ�
	int num = 0;
	//���ڼ��㹲�ж��ٸ����
	while (current)
	{
		current = current->pNext;
		num++;
	}
	//forѭ����ð�������һ�㣬whileѭ����ð������ڶ���
	for (int i = 0; i < num - 1; i++)//ð��˼�룬����num-1��
	{
		current = pHead;//ÿ�ζ���ͷ��ʼ��
		//cout << "��" << i + 1 << "�ν���ѭ��" << endl;//����ʱʹ��
		while (current->pNext)
		{
			//��ȡ���������ڵ������洢��ʱ������
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
			//ð����������ȳ��ֵĴ��ں���ֵ���ֱ�ӽ���
			//�����������ʱ����ȫ��ͬ�򲻽���
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
	cout << "��ӭ����ͳ�ƽ���" << endl;
	cout << "0.��ʾ�����˵�" << endl;
	cout << "1.���������ʾ�˵�" << endl << "2.�����·���ʾ�˵�" << endl << "3.����������ʾ�˵�" << endl;
	int choice;
	cout << "�������ѡ��" << endl;
	cin >> choice;
	if (choice!=0&&choice != 1 && choice != 2 && choice != 3) {
		cout << "Error:ѡ����󣡣���" << endl;
		BillStatistics();
	}

	int year = -1, month = -1, date = -1;

	switch (choice) {
	case 0:
		ShowList1(BillArrange(BillFectch()));
		break;
	case 1:
		cout << "�����ѯ���" << endl;
		cin >> year;
		cout << "Here is year" << endl;
		ShowYear(year);
		break;
	case 2:
		cout << "�����ѯ���" << endl;
		cin >> year;
		cout << "�����ѯ�·�" << endl;
		cin >> month;
		cout << "Here is month" << endl;
		ShowMonth(year,month);
		break;
	case 3:
		cout << "�����ѯ���" << endl;
		cin >> year;
		cout << "�����ѯ�·�" << endl;
		cin >> month;
		cout << "�����ѯ����" << endl;
		cin >> date;
		cout << "Here is date" << endl;
		ShowDate(year,month,date);
		break;
	}

	cout << endl << "�Ƿ�Ҫ���в鿴��" << endl;
	cout << "1.�����鿴" << endl;
	cout << "0.�˳��鿴" << endl;
	cout << "���ѡ��";
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
		cout << "Error:ѡ����󣡣���" << endl;
		system("cls");
		TallyBook();
	}
}

void ShowYear(int year)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//���ڶ�ȡfetch������
	Node1* Yhead = new Node1;//������ͷ���,����pNextָ���һ�����
	Node1* pre = Yhead;//�����������Ÿ�������
	int income = 0;//����
	int expense = 0;//֧��
	int change = 0;
	int i = 0;//���������������ж��������ݾ�����������
	//whileѭ�������������Ĵ����Լ���������������ļ�¼
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
	pre = Yhead;//��pre����ָ����
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
		cout << "����" << year << "������֧��ϸ" << endl;
		ShowList1(BillArrange(Yhead->pNext));
		cout << year << "�꣬��������" << income << "Ԫ,"
			<< "֧��" << expense << "Ԫ��" << endl;
		if (change > 0)
		{
			cout << "��һ�꣬�����ʲ�����" << change << "Ԫ" << endl;
		}
		else if (change == 0)
		{
			cout << "��һ�꣬�����ʲ��ޱ仯" << endl;
		}
		else
		{
			cout << "��һ�꣬�����ʲ�����" << (-change) << "Ԫ" << endl;
		}
	}
	else
	{
		cout << "��û����" << year << "�����֧��¼" << endl;
	}

}

void ShowMonth(int year, int month)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//���ڶ�ȡfetch������
	Node1* MOhead = new Node1;//������ͷ���,����pNextָ���һ�����
	Node1* pre = MOhead;//�����������Ÿ�������
	int income = 0;//����
	int expense = 0;//֧��
	int change = 0;
	int i = 0;//���������������ж��������ݾ�����������
	//whileѭ�������������Ĵ����Լ���������������ļ�¼
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
	pre = MOhead;//��pre����ָ����
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
		cout << "����" << year << "��" << month << "��������֧��ϸ" << endl;
		ShowList1(BillArrange(MOhead->pNext));
		cout << year << "��" << month << "�£���������" << income << "Ԫ, "
			<< "֧��" << expense << "Ԫ��" << endl;
		if (change > 0)
		{
			cout << "��һ�£������ʲ�����" << change << "Ԫ" << endl;
		}
		else if (change == 0)
		{
			cout << "��һ�£������ʲ��ޱ仯" << endl;
		}
		else
		{
			cout << "��һ�£������ʲ�����" << (-change) << "Ԫ" << endl;
		}
	}
	else
	{
		cout << "��û����" << year << "��" << month << "�µ���֧��¼" << endl;
	}

}

void ShowDate(int year, int month, int date)
{
	Node1* pHead = BillFectch();
	Node1* current = pHead;//���ڶ�ȡfetch������
	Node1* Dhead = new Node1;//������ͷ���,����pNextָ���һ�����
	Node1* pre = Dhead;//�����������Ÿ�������
	int income = 0;//����
	int expense = 0;//֧��
	int change = 0;
	int i = 0;//���������������ж��������ݾ�����������
	//whileѭ�������������Ĵ����Լ���������������ļ�¼
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
	pre = Dhead;//��pre����ָ����
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
		cout << "����" << year << "��" << month << "��" << date << "��������֧��ϸ" << endl;
		ShowList1(BillArrange(Dhead->pNext));
		cout << year << "��" << month << "��" << date << "����������" << income << "Ԫ, "
			<< "֧��" << expense << "Ԫ��" << endl;
		if (change > 0)
		{
			cout << "��һ�죬�����ʲ�����" << change << "Ԫ" << endl;
		}
		else if (change == 0)
		{
			cout << "��һ�죬�����ʲ��ޱ仯" << endl;
		}
		else
		{
			cout << "��һ�죬�����ʲ�����" << (-change) << "Ԫ" << endl;
		}
	}
	else
	{
		cout << "��û����" << year << "��" << month << "��" << date << "�յ���֧��¼" << endl;
	}

}

//�������������			2023.10.17����2023.10.10ʼ��







