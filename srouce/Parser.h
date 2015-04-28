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

	//
	bool Is_Keyword(Token token);		//�Ƿ�Ϊ�ؼ���
	void Parser_Var();					//����������������
	void Parser_Pra();					//��������
	void Parser_Math();					//��ѧ����ʽ
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