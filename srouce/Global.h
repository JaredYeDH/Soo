#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
//����֧�ֵ�����
enum Variable_Type
{
	Int,
	Char,
	Float,
	String
};
//�������
enum Ex_Statement
{

};
//�����ṹ��
typedef struct Variabledec
{
	Variable_Type variable_type;//��������
	string variable_name;		//��������
	union 
	{
		int Intvalue;
		char Charvalue;
		float Floatvalues;
		char * Strvalues;
	}Values;
};

#endif