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
	void Parsering(queue<Token> Queue);			//�����﷨����
};
inline Parser & Parser::Instance()
{
	Parser parser;
	return parser;
}
#endif