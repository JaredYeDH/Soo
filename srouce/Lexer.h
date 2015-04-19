#pragma once
#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <string>
#include <queue>
#include <boost/regex.hpp>
boost::smatch what;
boost::cmatch mat;
boost::regex expression("\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")|[A-Z_a-z][A-Z_a-z0-9]*|==|!=|<=|>=|&&|\\|\\||\\p{Punct})?");
using namespace std;

//�ַ�����Ԫ��
class Token
{
public:
	bool Id;		//��ʶ��
	bool Number;	//����
	int LineNumber;	//Token ����������
	string Text;	//�ı�
	Token();
	Token(int line);
	Token(int line, string &text, string Id_or_Number);
	int Token_GetLinenumber();
	bool Token_IsNumber();
	bool Token_IsId();
	string Token_GetText();
	int Token_GetNumber();
	bool operator!=(Token & example)
	{
		if (LineNumber != example.LineNumber)
			return false;
		else
			return true;
	}
};
Token StopEOF(-1);

//���дʷ�����
class Lexer
{
public:
	static Lexer & Instance(); //ʵ�����ʷ�����
	queue<Token> Queue; //�ʷ������Ľ��
	bool HasMore;
	Lexer();
	Token Lexer_Read();//��ȡһ���ַ�
	Token Lexer_Peek(int n);//Ԥ����һ���ַ�
	void Lexer_Readline(string &line, int linenumber);//��ȡһ�У����н���
	queue<Token> Lexer_ReturnQueue();//���شʷ������Ľ��
};
inline Lexer & Instance()
{
	Lexer Lexer_out;
	return Lexer_out;
}
#endif