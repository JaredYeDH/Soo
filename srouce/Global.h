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
	Void,
	Struct,
};
//��������״̬
enum External
{
	Global,		//��ʾ�����ⲿ����״̬
	Local,		//��ʾ�����ڲ�����״̬
};

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
//�������
enum Operator
{
	Plus,//+
	Minus,//-
};
//��־��������
enum TypeCode
{
	T_Int=0, //����
	T_Char=1,//�ַ���
	T_Float=2,//������
	T_Void=3,//������
	T_Ptr=4,//ָ��
	T_Func=5,//����
	T_Struct=6,//�ṹ��
	T_String=7,//�ַ���
	T_Array=8,//����
};
#endif