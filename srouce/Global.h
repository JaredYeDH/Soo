#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
//֧�ֵ���������
enum Data_Type
{
	Int,
	Char,
	Float,
	String,
	Void
};
//��������״̬
enum External
{
	Global,		//��ʾ�����ⲿ����״̬
	Local,		//��ʾ�����ڲ�����״̬
};

/*
*/
//�������
enum Ex_Statement
{
	Statement_Start, //������
	If_Statement,
	While_Statement,
	For_Statement,
	Continue_Statement,
	Break_Statement,
	Return_Statement
};

#endif