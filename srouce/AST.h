#pragma once
#ifndef _AST_H
#define _AST_H
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
#endif