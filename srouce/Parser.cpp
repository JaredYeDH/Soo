#include "Parser.h"
#include "Error.h"
#include "Global.h"
#include "API.h"
#include "SymbolTable.h"
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
//Token �Ƿ�Ϸ���Ԥ��
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
//�������Ƿ�Ϊ�ؼ���
bool Parser::Is_Keyword(Token token)
{
	string StrToken = token.Token_GetText();
	if (StrToken != "int"&&StrToken != "char"&&StrToken != "float"&&StrToken != "string"&&StrToken != "void"&&StrToken != "return"&&
		StrToken != "break"&&StrToken != "continue"&&StrToken != "struct")
		return true;
	else
		return false;
}
//�������Ƿ�Ϸ�
bool Parser::D_Legal(Token token)
{
	string StrToken = token.Token_GetText();
	char First = StrToken[0];
	if (First >= '0'&&First <= '9')
		return true;
	else
		return false;
}
//�������Ϸ��ж�
bool Parser::Declaration_Legal(Token token)
{
	bool is_Keyword, d_Legal;
	if (Is_Keyword(token))
		is_Keyword = true; //�ǹؼ���
	else
		is_Keyword = false; //���ǹؼ���
	if (D_Legal(token))
		d_Legal = true; //�ǺϷ���
	else
		d_Legal = false;//���ǺϷ���
	if (!is_Keyword&&d_Legal)
		return true;
	else
		return false;
}


//�������� �����ܣ������뺯������
void Parser::External_Dec(External state)
{
	Symbol_System::Symbol_SystemInstance().Symbol_CreateTree();//�������ű�ϵͳ���νṹ,�����������
	Symbol_System::Symbol_SystemInstance().SymbolPointer = Symbol_System::Symbol_SystemInstance().SymbolTreeRoot;//������㸳��ʵʱ���
	Symbol symboldata;
	if (!Type_Sign(symboldata)) //�����ж�
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Type", "declaration", "no such type");
		error.ThrowError();
	}
	if (symboldata.DType == T_Struct)
		Symbol_System::Symbol_SystemInstance().Symbol_Add(symboldata); //����ǽṹ���Ѿ��ж���ϣ�ֱ�Ӽ�����ű�����νṹ
	if (symboldata.Type==T_Struct&& Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		return;
	}
	while (1) //�������������������
	{
		Declarator(symboldata); //������ʶ��
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
		else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";") //��������
		{
			
		}
		else //�������
		{
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
			{
				Lexer::Lexer_Instance().Lexer_Read();//��ȡ��=��
				Init(); //������ֵ
			}
		}
	}
}
//�������ͷ���
bool Parser::Type_Sign(Symbol & symboldata)
{
	bool Type_Find = false;
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Read()))  //��ȡ����
	{
	case Char:
		symboldata.Type = T_Char;
		Type_Find = true;
	case Int:
		symboldata.Type = T_Int;
		Type_Find = true;
	case Float:
		symboldata.Type = T_Float;
		Type_Find = true;
	case Void:
		symboldata.Type = T_Void;
		Type_Find = true;
	case String:
		symboldata.Type = T_String;
		Type_Find = true;
	case Struct:
		Struct_Specifier(symboldata);  //�ṹ�����ͽ���
		symboldata.Type = T_Struct;
		Type_Find = true;
	default:
		break;
	}
	return Type_Find;
}
//Struct�ṹ�����ͽ���
void Parser::Struct_Specifier(Symbol & symboldata)
{
	Token token = Lexer::Lexer_Instance().Lexer_Read();// ��ȡ�ṹ������
	if (!Declaration_Legal(token)) //�ṹ�����ֺϷ����ж�
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Struct", "Struct  declaration", "Struct name is not legal");
		error.ThrowError();
	}
	symboldata.Name = token.Token_GetText(); //��ȡ�ṹ������
	if (Struct_Search(token) == NULL) //���û���ҵ�������ֵĽṹ��
	{
		symboldata.Type = T_Struct;

	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "{")
	{
		Struct_DeclarationList(symboldata); //�ṹ����������
	}
}
//Struct�ṹ����������
void Parser::Struct_DeclarationList(Symbol &symboldata)
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != "}")
	{
		Struct_Declaration(symboldata);
	}
	Lexer::Lexer_Instance().Lexer_Read();//��ȡ������
}
//Struct�ṹ������
void Parser::Struct_Declaration(Symbol & symboldata)
{
	Symbol StructAttribtues;
	Type_Sign(StructAttribtues); //���������ж�
	while (1)
	{
		Declarator(StructAttribtues);
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
			break;
		Token_Judge(",", "Struct", "Struct_Declaration", "need input a ','");
	}
	symboldata.Symbol_struct->Struct_Number.push_back(StructAttribtues);
}
//Struct�ṹ���Ƿ��Ѿ����ڣ������в��� 
Symbol* Parser::Struct_Search(Token token)
{
	
}
//������ֵ
void Parser::Init()
{
	Assign_Expression();
}
//���� ��ʶ��
void Parser::Declarator(Symbol & symboldata)
{
	Token token;
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsId)
	{
		token=Lexer::Lexer_Instance().Lexer_Read(); //��ȡ�����ʶ��
	}
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "need input a ID");
		error.ThrowError();
	}
	if (!Declaration_Legal(token)) //���ֺϷ����ж�
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Declarator", "  declaration", "Declarator name is not legal");
		error.ThrowError();
	}
	symboldata.Name = token.Token_GetText();//���ű��ȡ��ʶ��
	Declarator_Postfix(symboldata); //��������׺
}
//��������׺ �����жϺ��� ����������
void Parser::Declarator_Postfix(Symbol & symboldata)
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(")	//����
	{
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ������
		Symbol_Function  symbol_function;
		Func_ParameterList(symbol_function); //���������б����
		symboldata.Symbol_function = &symbol_function;
	}
	else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[") //����
	{
		int Length;
		Lexer::Lexer_Instance().Lexer_Read(); //��ȡ"["
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsNumber())
		{
			Length=Lexer::Lexer_Instance().Lexer_Read().Token_GetNumber(); //��ȡ �����С
		}
		Token_Judge("]", "Declarator_Postfix", "Array", "need input a ']'");
		Symbol_Array symbol_array;
		symbol_array.Length = Length;
		symboldata.Symbol_array = &symbol_array;
	}
}
//���������б����
void Parser::Func_ParameterList(Symbol_Function &symbol_funciton)
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		Symbol Func_Parameter;//��������
		if (!Type_Sign(Func_Parameter))
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "no such type");
			error.ThrowError();
		}
		Declarator(Func_Parameter); //ȷ�� ��ʶ��
		Symbol_FuncParam symbol_funcparam;
		symbol_funcparam.name = Func_Parameter.Name;
		symbol_funcparam.type = Func_Parameter.DType;
		symbol_funciton.Func_ParamList.push_back(symbol_funcparam);
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
/*
	������������ȼ����б�д��Ӧ�ĺ���Ƕ��
*/
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
//���ʽ�ĺ�׺
void Parser::Postfix_Expression()
{
	Variable_Expression();
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
//����ʵ�������ʽ
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
