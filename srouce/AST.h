#pragma once
#ifndef _AST_H
#define _AST_H
#include "Global.h"
#include "Lexer.h"
/*
	�����﷨������
*/
class AST
{
public:
	static AST & AST_Instance();
	void AST_Variabledec(Variabledec variable);	//��������
	void AST_Variabledef();
	void AST_Assign();							//��ֵ���
	void AST_If_Else();							//if_else �������
	void AST_Arithmetic();						//��������
	void AST_while();							//while���
	queue<Tree> ASyntax_Tree;					//�����﷨������
};
inline AST & AST::AST_Instance()
{
	AST ast;
	return ast;
}

#endif