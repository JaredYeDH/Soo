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
/*
���Ŵ洢�ṹ
*/
struct Symbol
{
	int Number;//���ŵĵ��ʱ���
	int Register;//���Ź����ļĴ���
	int Correlation_value;//���Ź���ֵ
	Symbol_Type Type;//������������
	Symbol * Next;//��������������
	Symbol * Prev_token;//ָ��ǰһ�����ͬ������
};

/*
	�������ͽṹ
*/
struct Symbol_Type
{
	int TypeCode;//��������
	struct Symbol * Ref; //���÷���
};

//���ű�ϵͳ
class Symbol_System
{
public:
	stack<Symbol> Global_Stack;//ȫ�ַ���ջ
	stack<Symbol> Local_Stack;//�ֲ�����ջ
	Symbol* Symbol_DirectPush(stack<Symbol> *stack,int number,Symbol_Type  type,int correlation_value);//������ѹ�����ջ
	Symbol *Symbol_Push(int number, Symbol_Type  type, int memory_type, int correlation_value);//������ѹ�����ջ����̬�ж�ȫ�ֻ�ֲ�
	Symbol *Symbol_FunctionPush(int number, Symbol_Type  type); //���������ŷ���ȫ�ַ��ű���
	Symbol *Symbol_VariablePush(Symbol_Type  type, int memory_type, int number, int address);//�ѱ���������ű���
	Symbol *Symbol_Search(int number);		//��ʶ������ 

};
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