#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
#include <vector>
#include <stack>
#include "Lexer.h"
#include "Global.h"
using namespace std;
/*
	���ű�ϵͳ
	�ڱ�������з��ű�������ų����г��ֵ��йر�ʶ����������Ϣ
*/
//����
//��ʶ���ṹ
struct Symbol
{
	char *Name;//��ʶ������
	TypeCode Type;//��ʶ������
	Data_Type DType;//��������
	int Level;//�������ڲ�� ��������
	int Address;//���ŵ�ַ����������������ġ����пռ䡱�е�λ��
	Symbol * Next_token;//ָ����һ�����ͬ������
};
//���ű�ϵͳ
class Symbol_System
{
public:
	static Symbol_System & Symbol_SystemInstance();//ʵ����
	stack<Symbol> Symbol_Stack;	//ȫ�ַ���ջ
	stack<int> Index_Stack;		//��������ջ
	void Symbol_Push(char *name, TypeCode type,Data_Type dtype,int level);//������ѹ�����ջ
	Symbol *Symbol_FunctionPush(int number, Symbol_Type  type); //���������ŷ���ȫ�ַ��ű���
	Symbol *Symbol_VariablePush(Symbol_Type  type, int memory_type, int number, int address);//�ѱ���������ű���
	Symbol *Symbol_Search(int number);		//��ʶ������ 

};
//����ϵͳ��ʵ����
Symbol_System & Symbol_System::Symbol_SystemInstance()
{
	Symbol_System sybol;
	return sybol;
}
/*
	���ʱ�ϵͳ
*/
#define Maxkey 1024 //��ϣ������

//���ʴ洢�ṹ����
struct TKWord
{
	int TKCode;//���ʱ���
	struct TKWord * Next;//ָ���ϣ��ͻ��ͬ���
	char *StrTK;//�����ַ���
	struct Symbol * symbol_struct;//ָ�򵥴�����ʾ�Ľṹ����
	struct Symbol * symbol_ID;//ָ�򵥴�����ʾ�ı�ʶ��
};
TKWord * TK_HasTable[Maxkey]; //���ʹ�ϣ��
vector<TKWord> TKArrayTable;//���ʱ�
#endif 