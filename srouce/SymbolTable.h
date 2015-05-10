#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include "Lexer.h"
#include "Global.h"
using namespace std;
/*
	���ű�ϵͳ
	�ڱ�������з��ű�������ų����г��ֵ��йر�ʶ����������Ϣ
*/
//������������
struct Symbol_Array
{
	int Length;//����ά��
};
//������ʽ����
struct Symbol_FuncParam
{
	Data_Type type;//��������
	string name; //��������
};
//�ṹ����������
struct Symbol_Struct
{
	vector<Symbol> Struct_Number;//�ṹ���е����ݳ�Ա
};
//������������
struct Symbol_Function
{
	Data_Type Func_Type;//������������
	int Func_Address;//������ڵ�ַ
	vector<Symbol_FuncParam> Func_ParamList;//��������ʽ����
};

//��ʶ���ڵ�ṹ
struct Symbol
{
	string Name;//��ʶ������
	TypeCode Type;//��ʶ������
	Data_Type DType;//��������
	int Address;//���ŵ�ַ����������������ġ����пռ䡱�е�λ��
	Symbol_Array * Symbol_array;//��ʶ����ʾ������Ϊ����
	Symbol_Function * Symbol_function;//��ʶ����ʾ������Ϊ����
	Symbol_Struct * Symbol_struct;//��ʶ����ʾ������Ϊ�ṹ��
	SymbolTable_Node * Link;//��ͬ������ı�ʶ��
};
//���ű����ṹ
struct SymbolTable_Node
{
	Symbol SymbolData;//�ڵ�����
	SymbolTable_Node * Root;	//���ڵ�
	SymbolTable_Node * Child;	//�ӽڵ�
};
//���ű�ϵͳ��
class Symbol_System
{
public:
	static Symbol_System & Symbol_SystemInstance();	//ʵ����
	static SymbolTable_Node * SymbolPointer;//���дʷ�����ʱ���ű��ʵʱָ��
	SymbolTable_Node * SymbolTreeRoot;					//���ű�����ṹ���ڵ�
	void Symbol_CreateTree();							//�������ű�ϵͳ���νṹ
	void Symbol_Add(string name, TypeCode type,Data_Type dtype);//�����ż������νṹ���ű�ϵͳ
	void Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype);//�����Ŵ����νṹ���ű�ϵͳɾ��
	Symbol *Symbol_Search(int number);		//��ʶ�����ң������ز��ҵ��ķ��Žڵ㣬��������ڷ���NULL

};
//����ϵͳ��ʵ����
Symbol_System & Symbol_System::Symbol_SystemInstance()
{
	Symbol_System sybol;
	return sybol;
}

#endif 