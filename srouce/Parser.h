#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include <string>
#include "Lexer.h"
#include "Global.h"
#include "SymbolTable.h"
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
	bool Type_Sign(Symbol_Type *symboltype);//�ж��Ƿ�Ϊ���ͷ���
	void Declarator();					//������
	void Funbody();						//������
	bool Is_Keyword(Token token);		//�������Ƿ�Ϊ�ؼ���
	bool D_Legal(Token token);			//�ַ������Ƿ�Ϸ�
	bool Declaration_Legal(Token token);//�������Ϸ��ж�
	void Init();						//��ֵ��
	void Declarator_Postfix();			//�������ź�׺
	void Struct_Specifier(Symbol_Type *symboltype);//�ṹ�����ͽ���
	void Struct_DeclarationList();		//�ṹ��������
	void Struct_Declaration();			//�ṹ������
	Symbol* Struct_Search(Token token);	//�ṹ�嶨�����
	void ParameterList();				//��ʽ�����б�
	void ArgumentList();				//ʵ�α��ʽ�б�
	void Compound_Statement();          //�������
	void Statement();					//���
	void Statement_If();				//If���
	void Statement_While();				//While���
	void Statement_For();				//For���
	void Statement_Return();			//Return���
	void Statement_Continue();			//Continue���
	void Statement_Break();				//Break���
	void Statement_Expression();		//���ʽ
	void Token_Judge(string token,string module,string function,string error);		//Token �ж�
	void Assign_Expression();			//��ֵ���ʽ
	void Equal_Expression();			//��ȱ��ʽ
	void Relation_Expression();			//��ϵ���ʽ
	void Add_Expression();				//�Ӽ�����ʽ
	void Multilpi_Expression();			//�˳�����ʽ
	void Unary_Expression();			//һԪ������ʽ
	void Postfix_Expression();			//��׺���ʽ
	void Variable_Expression();			//��������
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif