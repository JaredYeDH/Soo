#pragma once
#ifndef _PARSER_H
#define _PARSER_H
/*
		�﷨����
*/
class Parser
{
public:
	static Parser & Instance();
	void Parsering();			//�����﷨����
};
inline Parser & Instance()
{
	Parser parser;
	return parser;
}
#endif