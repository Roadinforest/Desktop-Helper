#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define Filename1 "BillDate.dat"
#define Outlay 0
#define Income 1

class Bill {
private:
	int year_;
	int month_;
	int date_;
	int hour_;
	int min_;

	int value_;//The value of the account
	string note_;

	int case_;//

public:
	Bill(int value=0, int year=0, int month=0, int date=0, 
		int hour=0, int min=0, string note="Nothing", bool Case = 0) {
		value_ = value;
		year_ = year;
		month_ = month;
		date_ = date;
		hour_ = hour;
		min_ = min;
		note_ = note;
		case_ = Case;
	}
	//The constructor
	void ShowRecord(void);

	//һ�ѽӿ�
	//The reader��ȡ����
	int GetYear(void);
	int GetMonth(void);
	int GetDate(void);
	int GetHour(void);
	int GetMin(void);
	int GetValue(void);
	int GetCase(void);
	string GetNote(void);

	//The writerд������
	void SetYear(int year);
	void SetMonth(int month);
	void SetDate(int date);
	void SetHour(int hour);
	void SetMin(int min);
	void SetValue(int value);
	void SetCase(int Case);
	void SetNote(string name);
};

struct Node1 {
	Bill value;
	Node1* pNext;
};//����һ�����

//----------service----------

void SaveList1(Node1* pHead);
//������ʱ�洢������

void BillAdd(void);
//����˵�����������

void BillDelete(void);
//ɾ����Ӧnum��Ŷ�Ӧ�Ľ��

Node1* BillFectch(void);
//���������ļ��д洢���������ݵ������ͷ���

void BillChange(void);
//�޸�ĳ���˵�������

Node1* BillArrange(Node1* given);
//����һ���Ѿ�����ʱ��˳���źõ�����ͷ���

void BillReplace(Node1* pHead);
//�������ļ��е������Ը�����������

void Swap(Node1* current);
//���ý�������һ���������滻

bool IsRun(int year);
//�ж���������Ƿ�Ϊ����

int ReturnDay(int year,int month);
//��������Ƿ�Ϊ���꣬�Լ��·ݷ��ظ���Ӧ���ж�����

//----------service----------

//----------view----------


void BillModify(void);
//�޸��˵�����������

void BillStatistics(void);
//ͳ���˵�����������

void BillQuit(void);
//�˳����˱�����������

void ShowList1(Node1* pHead);
//��ʾ�������������

void TallyBook(void);
//���˱��Ĳ˵�����

void BillShow(void);
//�������ļ��ж�ȡ���ݲ��ҽ�����ʾ

void ShowYear(int year);
//��ʾyear��ݵ������˵�

void ShowMonth(int year,int month);
//��ʾyear�����month�·ݵ��˵�

void ShowDate(int year, int month,int date);
//��ʾyear�����month�·�day����˵�

//----------view---------

