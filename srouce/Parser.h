#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include "Lexer.h"
#include "Global.h"
using namespace std;
/*
		�﷨����
*/
class Parser
{
public:
	static Parser & Parser_Instance();	//�﷨����ʵ����
	void Parsering(queue<Token> Queue);	//�����﷨����
	void External_Dec(External state);  //�����ⲿ����
	bool Type_Sign();					//�ж��Ƿ�Ϊ���ͷ���
	void Declarator();					//������
	void Funbody();						//������
	void Init();						//��ֵ��
	void Declarator_Postfix();			//�������ź�׺
	void ParameterList();				//�����б�
	void Compound_Statement();          //�������
	void Statement();					//���
	void Statement_If();				//If���
	void Statement_While();				//While���
	void Statement_For();				//For���
	void Statement_Return();			//Return���
	void Statement_Continue();			//Continue���
	void Statement_Break();				//Break���
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif