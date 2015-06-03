#include "API.h"
#include "Parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//�ַ�����ϣ����
int API::Elf_Hash(char * key)
{
	int  h = 0, g;
	while (*key) {
		h = (h << 4) + *key++;
		if (g = h & 0xf0000000)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}
//string תint
int API::String2Int(string str)
{
	int number = atoi(str.c_str());
	return number;
}
//int תstring
string API::Int2String(int number)
{
	stringstream ss;
	string str;
	ss << number;
	ss >> str;
	return str;
}
//string תfloat
float API::String2Float(string str)
{
	float number = atof(str.c_str());
	return number;
}
//stringn תchar *
char* API::String2CharPlus(string str)
{
	char * Char = new char[str.size()];
	strcpy(Char, str.data());
	return Char;
}
//Token ת Data_Type
Data_Type API::Token2Type(Token token)
{
	if (token.Token_GetText() == "int")
		return Int;
	if (token.Token_GetText() == "char")
		return Char;
	if (token.Token_GetText() == "float")
		return Float;
	if (token.Token_GetText() == "void")
		return Void;
	if (token.Token_GetText() == "string")
		return String;
}
//Token ת Ex_Statement
Ex_Statement API::Token2Statement(Token token)
{
	if (token.Token_GetText() == "{")
		return Statement_Start;
	if (token.Token_GetText() == "if")
		return If_Statement;
	if (token.Token_GetText() == "for")
		return For_Statement;
	if (token.Token_GetText() == "while")
		return While_Statement;
	if (token.Token_GetText() == "break")
		return Break_Statement;
	if (token.Token_GetText() == "continue")
		return Continue_Statement;
	if (token.Token_GetText() == "return")
		return Return_Statement;
}
//Token ת Operator
Operator API::Token2Operator(Token token)
{
	if (token.Token_GetText() == "+")
		return Plus;
	if (token.Token_GetText() == "-")
		return Minus;
	else
	{
		Error
	}
}
//��ӭ����
void API::API_Welcome()
{
	string command;
	cout << "       Welcome to Soo       " << endl;
	cout << "            by:Leviathan1995" << endl;
	cout << "File or Input: f or i       " << endl;
	cout << "Please select:              " << endl;
	cin >> command;
	if (command == "f")
		API_ReadFile();
	else
		API_ShellInput();
}

//���ļ��ж�ȡ����
void API::API_ReadFile()
{
	int LineNumber = 0;
	Token token;
	ifstream Infile("code.txt");
	string Line;
	while (getline(Infile, Line))
	{
		LineNumber++;
		Lexer::Lexer_Instance().Lexer_Readline(Line, LineNumber);
	}
	Queue = Lexer::Lexer_Instance().Lexer_ReturnQueue();
	API::Instance().API_Parser(Queue);
}

//�����﷨����
void API::API_Parser(queue<Token> Queue)
{
	Parser::Parser_Instance().Parsering(Queue);
}