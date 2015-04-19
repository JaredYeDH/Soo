#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include "Lexer.h"
using namespace std;
/*
		�﷨����
*/
class Parser
{
public:
	static Parser & Instance();
	void Parsering(queue<Token> Queue);	//�����﷨����
	void Parser_Dec();					//������������
	void Parser_If();					//if else���
};
inline Parser & Parser::Instance()
{
	Parser parser;
	return parser;
}
#endif