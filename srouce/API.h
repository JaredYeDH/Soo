#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
#include <string>
using namespace std;
class API
{
public:
	/*
		���߷���
	*/
	int String2Int(string str);
	string Int2String(int number);
	float String2Float(string str);
	char * String2CharPlus(string str);
	/*
		������
	*/
	static API & Instance();
	queue<Token> Queue;							//�ʷ������Ľ��
	void API_Welcome();							//��ӭ����
	void API_ReadFile();						//���ļ��ж�ȡ����
	void API_ShellInput();						//����̨�������
	void API_Parser(queue<Token> Queue);		//�﷨����
	bool API_VariableFind(string variablename);	//�� Pra_Variable �в��ұ���		
	Variable API_ReturnVar(string variablename);//���ز��ҵı���
	/*
		���ݴ洢
	*/
	vector<Variable> Pra_Variable; //ȫ�ֱ���
};
inline API &API::Instance()
{
	API API_Instance;
	return API_Instance;
}
#endif
