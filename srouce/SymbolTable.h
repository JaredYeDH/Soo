#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
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
	Data_Type Type;//������������
	Symbol * Next;//��������������
	Symbol * Prev_token;//ָ��ǰһ�����ͬ������
};
//���ű�ϵͳ
class Symbol_System
{
public:
	stack<Token> Global_Stack;//ȫ�ַ���ջ
	stack<Token> Local_Stack;//�ֲ�����ջ
	Symbol *Symbol_DirectPush(stack< Token> * stack,int number,Data_Type * type,int correlation_value);//������ѹ�����ջ
	Symbol *Symbol_Push(int number, Data_Type* type, int memory_type, int correlation_value);//������ѹ�����ջ����̬�ж�ȫ�ֻ�ֲ�
	Symbol *Symbol_FunctionPush(int number, Data_Type * type); //���������ŷ���ȫ�ַ��ű���
	Symbol *Symbol_VariablePush(Data_Type * type, int Register, int number, int address);//�ѱ���������ű���

};
#endif 