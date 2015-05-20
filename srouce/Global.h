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
	Array,
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
	T_Short=2,//������
	T_Void=3,//������
	T_Ptr=4,//ָ��
	T_Func=5,//����
	T_Struct=6,//�ṹ��
	T_String=7,//�ַ���
	T_Array=8,//����
	T_Btype=0x000f,//������������
};
//�Ĵ�������
enum Register
{
	REG_EAX=0,
	REG_ECX,
	REG_EDX,
	REG_EBX,
	REG_ESP,
	REG_EBP,
	REG_ESI,
	REG_EDI,
	REG_ANY
};
#define REG_IRET REG_EAX //ָ��EAXΪ��ŷ���ֵ�ļĴ���
//Ѱַ��ʽ
enum AddressForm
{
	ADDR_OTHER,//�Ĵ������Ѱַ
	ADDR_REG=3,//�Ĵ���ֱ��Ѱַ
};
//�洢����
enum StorageType
{
	Soo_Global=0x00f0,//�������ͳ������ַ��������ַ���������ȫ�ֱ�������������
	Soo_Local=0x00f1,	//ջ�б���
	Soo_Valmask=0x00ff,	//�洢��������
	Soo_Lval=0x0100,	//��ֵ
};
#endif