#include "Parser.h"

#include "Error.h"
#include "Global.h"
#include "API.h"
using namespace std;
//�﷨����
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Lexer_Instance().Lexer_Read() != StopEOF)
	{
		External_Dec(Global);
	}
}
//���� ����
void Parser::External_Dec(External state)
{
	if (!Type_Sign()) //�����ж�
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
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "{") // ��������
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
//���� ��ʶ��
void Parser::Declarator()
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsId)
	{
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ�����ʶ��
	}
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "need input a ID");
		error.ThrowError();
	}
	Declarator_Postfix(); //��������׺
}
//��������׺
void Parser::Declarator_Postfix()
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(")	//����
	{
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ������
		ParameterList(); //�����б����
	}
	else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[") //����
	{
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ"["
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsNumber())
		{
			Lexer::Lexer_Instance().Lexer_Read(); //��ȡ �����С
		}
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "]")
			Lexer::Lexer_Instance().Lexer_Read(); //��ȡ"]"
		else
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "need input  a ']'");
			error.ThrowError();
		}

	}
}
//�����б����
void Parser::ParameterList()
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		if (!Type_Sign())
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "no such type");
			error.ThrowError();
		}
		Declarator(); //ȷ�� ��ʶ��
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == ",")
		{
			Lexer::Lexer_Instance().Lexer_Read();//��ȡ��=��
			continue;
		}
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == ")")
		Lexer::Lexer_Instance().Lexer_Read();
}
//������
void Parser::Funbody()
{
	Compound_Statement(); //�������
}
//�������
void Parser::Compound_Statement()
{
	while (!Type_Sign()) 
	{
		Parser::Parser_Instance().External_Dec(Local);//�ڲ����� �� ����
	}
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != "}")
	{
		Statement();//���
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == "}")
		Lexer::Lexer_Instance().Lexer_Read();
}
//���
void Parser::Statement()
{
	Token token = Lexer::Lexer_Instance().Lexer_Peek(0);
	switch (API::Instance().Token2Statement(token))
	{
	case Statement_Start: //��� Ϊ ������ ���������
			Compound_Statement();
	case If_Statement:
			Statement_If();
	case For_Statement:
			Statement_For();
	case While_Statement:
			Statement_While();
	case Return_Statement:
			Statement_Return();
	case Break_Statement:
			Statement_Break();
	case Continue_Statement:
			Statement_Continue();
	default:
		break;
	}
}
//If���
void Parser::Statement_If()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ �ؼ��� ��IF��
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(") //IF����е��жϱ��ʽ
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IF", "If_Statement", "need input a '('");
		error.ThrowError();
	}
	Expression();  //�жϱ��ʽ
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ")")
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IF", "If_Statement", "need input a ')'");
		error.ThrowError();
	}
	Statement();
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "else")
	{
		Lexer::Lexer_Instance().Lexer_Read();//��ȡ else
		Statement();
	}

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
