#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
#include "Global.h"
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
	Data_Type Token2Type(Token token);  //token ת ��������
	Ex_Statement Token2Statement(Token token);//token ת �������
	Operator Token2Operator(Token token); //token ת �����
	int Elf_Hash(char * key);			//���ű�ʹ�ã���ϣ�����������ϣ��ַ
	/*
		������
	*/
	static API & Instance();
	queue<Token> Queue;							//�ʷ������Ľ��
	void API_Welcome();							//��ӭ����
	void API_ReadFile();						//���ļ��ж�ȡ����
	void API_ShellInput();						//����̨�������
	void API_Parser(queue<Token> Queue);		//�﷨����
};
inline API &API::Instance()
{
	static API API_Instance;
	return API_Instance;
}
#endif
