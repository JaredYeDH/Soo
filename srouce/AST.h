#pragma once
#ifndef _AST_H
#define _AST_H
#include "Lexer.h"
/*
	�����﷨������
*/
class AST
{
public:
	void AST_Variabledec();//������������
	void AST_Assign(); //��ֵ���
	void AST_If_Else();//if_else �������
	void AST_Arithmetic();//��������
	void AST_while();	//while���
};
//���ڵ�
struct Tree_Node
{
	Token token;//����ֵ
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