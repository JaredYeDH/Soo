#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
using namespace std;
/*
	ʵ��һ����̬ջ
*/
class Stack
{
public:
	Stack(); //ջ�ĳ�ʼ��
	Stack(int size);//ջ�ĳ�ʼ��
	~Stack();//ջ������
	void * Base; //ջ��ָ��
	void * Top;  //ջ��ָ��
	int StackSize;//ջ�Ĵ�С
	void * Stack_Push( void * value);//ѹջ��������ջ��Ԫ��
	void * Stack_Pop(); //����ջ��Ԫ��
	void * Stack_Top();//����ջ��Ԫ��
	bool * Stack_Empty();//ջ�Ƿ�Ϊ��
};
#endif 