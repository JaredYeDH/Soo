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
//Token �ж�
void Parser::Token_Judge(string token, string module, string function, string error)
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == token)
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber,module, function, error);
		error.ThrowError();
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
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "need input a ID");
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
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "need input  a ']'");
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
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "no such type");
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
		Statement_Expression();//���ʽ
		break;
	}
}
//If���
void Parser::Statement_If()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ �ؼ��� ��IF��
	Token_Judge("(", "If", "If_Statement", "need input a '('");
	Statement_Expression();  //�жϱ��ʽ
	Token_Judge(")", "If", "If_Statement", "need input a ')'");
	Statement();//����
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "else")
	{
		Lexer::Lexer_Instance().Lexer_Read();//��ȡ else
		Statement();
	}
}
//while���
void Parser::Statement_While()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ �ؼ��� ��While��
	Token_Judge("(", "While", "While_Statement", "need input a '('");
	Statement_Expression();  //�жϱ��ʽ
	Token_Judge(")", "While", "While_Statement", "need input a ')'");
	Statement();//����
}
//For���
void Parser::Statement_For()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ�ؼ��� ��for��
	Token_Judge("(", "For", "For_Statement", "need input a '('");
	Statement_Expression();//�жϱ��ʽ
	Token_Judge(";", "For", "For_Statement", "need input a ';'");
	Statement_Expression();//�жϱ��ʽ
	Token_Judge(";", "For", "For_Statement", "need input a ';'");
	Statement_Expression();//�жϱ��ʽ
	Token_Judge(")", "For", "For_Statement", "need input a ')'");
	Statement();//����
}
//Return  ���
void Parser::Statement_Return()
{
	Lexer::Lexer_Instance().Lexer_Read(); //��ȡ "return "
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ ��;"
	else
	{ 
		Statement_Expression();  //����return ***;
		Token_Judge(";", "Return", "Return_Statement", "need input a ';'");
	}
}
//Break ���
void Parser::Statement_Break()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ ��Break"
	Token_Judge(";", "Break", "Break_Statement", "need input a ';'");
}
//continue ���
void Parser::Statement_Continue()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ continue 
	Token_Judge(";", "Continue", "Continue_Statement", "need input a ';'");
}
//Expreesion ���ʽ
void Parser::Statement_Expression()
{
	while (1)
	{
		Assign_Expression();
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ",")
			break;
	}
}
//��ֵ���ʽ
void Parser::Assign_Expression()
{
	Equal_Expression();
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
	{
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ ��=��
		Assign_Expression();
	}
}
//��ȱ��ʽ
void Parser::Equal_Expression()
{
	Relation_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "==" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "!=")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Relation_Expression();
	}
}
//��ϵ���ʽ
void Parser::Relation_Expression()
{
	Add_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "<" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ">"
		|| Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "<=" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ">=")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Add_Expression();
	}
}
//�Ӽ�����ʽ
void Parser::Add_Expression()
{
	Multilpi_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "+" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "-")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Multilpi_Expression();
	}
}
//�˳�����ʽ
void Parser::Multilpi_Expression()
{
	Unary_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "*" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "/")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
	}
}
//һԪ������ʽ
void Parser::Unary_Expression()
{
	switch (API::Instance().Token2Operator(Lexer::Lexer_Instance().Lexer_Peek(0)))
	{
	case Plus:
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
		break;
	case Minus:
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
		break;
	default:
		Postfix_Expression();
		break;
	}
}
//��׺���ʽ
void Parser::Postfix_Expression()
{
	Primary_Expression();
	while (1)
	{
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(") //����
			ArgumentList();
		else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[")
		{
			Lexer::Lexer_Instance().Lexer_Read();
			Statement_Expression();
			Token_Judge("]", "Postfix", "Postfix_Expression", "need input a ']'");
		}
	}
}
//��������
void Parser::Variable_Expression()
{
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Peek(0)))
	{
	case Int:
	case Char:
	case Float:
	case String:
		break;
	default:
	{
			   Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Variable", "Variable_Expression", "no such type variable");
			   error.ThrowError();
			   break;
	}
	}
}
//ʵ�������ʽ
void Parser::ArgumentList()
{
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ "("
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		for (;;)
		{
			Assign_Expression();
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ")")
				break;
			Token_Judge(",", "ArgumentList", "Parameter list ", "need input a ','");
		}
	}
	Token_Judge(")", "ArgumentList", "Parameter list ", "need input a ')'");
}
