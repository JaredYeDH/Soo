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
		if (token.Token_GetText() == "Var")		//��������������
			Parser_Var();
		if (token.Token_GetText() == "Program")	//������
			Parser_Pra();

	}
}
//��������������
void Parser::Parser_Var()
{
	Token token = Lexer::Lexer_Instance().Lexer_Read();//��ȡ"Var"
	token = Lexer::Lexer_Instance().Lexer_Read();	//��ȡ":"
	if (token.Token_GetText() != ":")
	{
		Error error(token.Token_GetLinenumber, "Variable", "Parser_Var", "need a '��'");
		error.ThrowError();
	}
	while (API::Instance().String2CharPlus(Lexer::Lexer_Instance().Lexer_Read().Token_GetText()) != "Program")
	{
		if (token.Token_GetText() == "dec") //�����������
			Parser_Dec();
		if (token.Token_GetText() == "def") //����������
			Parser_Def();
		if (token.Token_GetText() == "\\n") //����ǻ��з���
			continue;
	}
}
//��������
void Parser::Parser_Dec()
{
	Variable NewVariable;
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
//��������
void Parser::Parser_Def()
{
	Lexer::Lexer_Instance().Lexer_Read(); //��ȡdef
	Variable variable;
	Token token = Lexer::Lexer_Instance().Lexer_Read();
	string variablename = token.Token_GetText(); //��ȡ������
	for (auto i = API::Instance().Pra_Variable.begin(); i != API::Instance().Pra_Variable.end(); i++)
	{
		if (variablename == i->variable_name)
		{
			variable = *i;
			break;
		}
	}
	if (API::Instance().API_VariableFind(variablename)) //�����������,if����
	{
		variable = API::Instance().API_ReturnVar(variablename);
		switch (variable.variable_type)
		{
		case Int:
			variable.Values.Intvalue = API::Instance().String2Int(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;
		case Float:
			variable.Values.Floatvalue = API::Instance().String2Float(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;
		case Char:
			variable.Values.Charvalue = API::Instance().String2Int(Lexer::Lexer_Instance().Lexer_Read().Token_GetText[0]);
			break;
		case String:
			variable.Values.Strvalue = API::Instance().String2CharPlus(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;

		}
	}
	else  //����������
	{
		Error error(token.Token_GetLinenumber, "Variable", "declaration", "no such variable");
		error.ThrowError();
	}

}