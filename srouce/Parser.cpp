#include "Parser.h"
#include "AST.h"
#include "Error.h"
#include "Global.h"
#include "API.h"
using namespace std;
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Lexer_Instance().Lexer_Read() != StopEOF)
	{
		External_Dec(Global);
	}
}
//�����ⲿ����
void Parser::External_Dec(External state)
{
	if (!Type_Sign())
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Type", "declaration", "no such type");
		error.ThrowError();
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		return;
	}
	while (1) //�������������������
	{
		Declarator();
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "{")
		{
			if (state == Local)
			{
				Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Dec", "declaration", "not support function nest");
				error.ThrowError();
			}
			Funbody();//������
			break;
		}
		else
		{
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
			{
				Lexer::Lexer_Instance().Lexer_Read();//��ȡ��=��
				Init();
			}
		}
	}
}
void Parser::Declarator()
{

}
//�������ͷ���
bool Parser::Type_Sign()
{
	bool Type_Find = false;
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Read()))
	{
	case Char:
		Type_Find = true;
	case Int:
		Type_Find = true;
	case Float:
		Type_Find = true;
	case Void:
		Type_Find = true;
	case String:
		Type_Find = true;
	default:
		break;
	}
	return Type_Find;
}
