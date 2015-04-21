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
	static Parser & Parser_Instance();
	bool Is_Keyword(Token token);		//�Ƿ�Ϊ�ؼ���
	void Parsering(queue<Token> Queue);	//�����﷨����
	void Parser_Var();					//��������������
	void Parser_Pra();					//������
	void Parser_Keyword();				//�ؼ��ֽ���
	void Parser_Dec();					//��������
	void Parser_Def();					//��������
	void Parser_If();					//if else���
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif