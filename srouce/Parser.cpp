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
		token = Lexer::Lexer_Instance().Lexer_Peek(0);
		if (token.Token_GetText() == "dec") //�����������
			Parser_Dec();
		if (token.Token_GetText() == "def") //����������
			Parser_Def();
		if (token.Token_GetText() == "if")  //if else ����
			Parser_If();

	}
}
//�����������
void Parser::Parser_Dec()
{
	Variabledec NewVariable;
	Lexer::Lexer_Instance().Lexer_Read(); //��ȡdec
	Token token = Lexer::Lexer_Instance().Lexer_Read();
	string Type =token.Token_GetText();//��ȡ����
	if (Type == "int")
		NewVariable.variable_type == Int;
	else if (Type == "char")
		NewVariable.variable_type == Char;
	else if (Type == "float")
		NewVariable.variable_type == Float;
	else if (Type == "string")
		NewVariable.variable_type == String;
	else
	{
		Error error(token.Token_GetLinenumber, "Variable", "declaration", "no such type");
		error.ThrowError();
	}
	string name = Lexer::Lexer_Instance().Lexer_Read().Token_GetText();
	NewVariable.variable_name = name;
	AST::AST_Instance().AST_Variabledec(NewVariable);
}