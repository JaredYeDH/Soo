#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
class API
{
public:
	static API & Instance();
	queue<Token> Queue;							//�ʷ������Ľ��
	void API_Welcome();							//��ӭ����
	void API_ReadFile();						//���ļ��ж�ȡ����
	void API_ShellInput();						//����̨�������
	void API_Parser(queue<Token> Queue);		//�﷨����
};
inline API &API::Instance()
{
	API API_Instance;
	return API_Instance;
}
#endif
