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
typedef struct Variable
{
	Variable_Type variable_type;//��������
	string variable_name;		//��������
	union 
	{
		int Intvalue;
		char Charvalue;
		float Floatvalue;
		char * Strvalue;
	}Values;
};
//���ڵ�
struct Tree_Node
{
	string token;//����ֵ
	string Sign;//���ı�־
	Tree_Node * Left;
	Tree_Node * Right;

};
//�﷨��
struct Tree
{
	Tree_Node Root;
	Tree_Node * Left;
	Tree_Node * Right;
};
#endif