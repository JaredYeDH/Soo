/*
		�﷨����
*/
#ifndef PARSERHEAD_H_
#define PARSERHEAD_H_
#include "LexerHead.h"
#include <string>
using namespace std;
/*
����
*/
//��������
typedef enum
{
	Boolean_value = 1,
	Int_value,
	Double_value,
	String_value,
	NULL_value
}Value_type;
//�����Ľṹ��
struct Variable_
{
	Value_type type; //����������
	union
	{
		bool boolean_value;
		int int_vlaue;
		double double_value;
		string *string_value; //�ַ���ֵ
	}u;
};
//ȫ�ֱ�������
struct Variable_tag
{
	string name; //����������
	Variable_ value;//������ֵ
	Variable_tag *next;//��һ������
};
/*
	���ʽ
*/
//���еı��ʽ���͵�ö��
typedef enum {
	BOOLEAN_EXPRESSION = 1, //bool�ͳ���
	INT_EXPRESSION,   //int�ͳ���
	DOUBLE_EXPRESSION,//double�ͳ���
	STRING_EXPRESSION,//�ַ����ͳ���
	IDENTIFIER_EXPRESSION,//����
	ASSIGN_EXPRESSION,//��ֵ���ʽ
	ADD_EXPRESSION,//��ӱ��ʽ
	SUB_EXPRESSION,//�������ʽ
	MUL_EXPRESSION,//�˷����ʽ
	DIV_EXPRESSION,//�������ʽ
	MOD_EXPRESSION,//������ʽ
	EQ_EXPRESSION,//==
	NE_EXPRESSION,//!=
	GT_EXPRESSION,//>
	GE_EXPRESSION,//>=
	LT_EXPRESSION,//<
	LE_EXPRESSION,//<=
	LOGICAL_AND_EXPRESSION,//&&
	LOGICAL_OR_EXPRESSION,//||
	FUNCTION_CALL_EXPRESSION,//�������ñ��ʽ
	MINUS_EXPRESSION,
	NULL_EXPRESSION,
	EXPRESSION_TYPE_COUNT_PLUS_1,
	//BOOLEAN_EXPRESSION	Bool_expression; //bool�ͳ���
	//ADD_EXPRESSION		Add_expreesion; //��ӱ��ʽ
	//SUB_EXPRESSION	Sub_expreesion;//�������ʽ
	//MUL_EXPRESSION	Mul_expreesion;	//�˷����ʽ
	//DIV_EXPRESSION	Div_expreesion;//�������ʽ
	//MOD_EXPRESSION  Mod_expreesion;//������ʽ
	//FUNCTION_CALL_EXPRESSION,//�������ñ��ʽ
} ExpressionType;
//�����ʽ���Ľ�������ö��
typedef enum
{
	Variable = 1,//�ڵ��Ǳ���
	Number,//�ڵ�������
	Sign,//�ڵ��Ƿ���
}Statementtype;

//�������ʽ�����ṹ
struct Binary_Tree
{
	char data;
	Binary_Tree *left;
	Binary_Tree *right;
};
/*
		�ж��������ʽ
*/
//�ж��������ʽ���ṹ��
struct Expression_tag {
	ExpressionType type;
	int line_number;
	union {
		bool             boolean_value;
		int                     int_value;
		double                  double_value;
		char                    *string_value;
		//ASSIGN_EXPRESSION      assign_expression;
		/*
		char                    *identifier;
		BinaryExpression        binary_expression;
		Expression              *minus_expression;
		FunctionCallExpression  function_call_expression;
		*/
	} u;
};
//�жϱ��ʽ���﷨�������Ľ������
typedef enum
{
	charSign = 1,
	judge_Number,
	Bool
}Tree_Judge_Type;
//�����жϱ��ʽ���﷨������
struct Tree_Judge
{
	Tree_Judge_Type type;
	union
	{
		char* sign;		//�ڵ��������
		int data;	//�ڵ�����ֵ
		bool bool_output;//���������ıȽϽ��
	}u;
	Tree_Judge *left;
	Tree_Judge *right;
};
/*
		����Block
*/
//�����ַ�������
struct Block_Token
{
	Token This;
	Block_Token *next;
};
//���ṹ��
struct StatementLink
{
	ExpressionType type;//�������
	Block_Token * head;//����

};
//����ṹ��
struct Block
{
	StatementLink *statementlist;
	StatementLink *next;
};

//��ֵ���ʽ�����νṹ
struct Assign_Tree
{
	Binary_Tree * right;
	Variable_ left;
};
/*
		�ؼ���
*/
//�ؼ����������
typedef enum
{
	WHILE_STATEMENT
}KeyStatementType;
//while���Ľṹ
struct WhileStatement
{
	Expression_tag *condition;//�������ʽ
	Block* block; //��ִ�п�
};
//�ؼ������ṹ��
struct Statement_tag
{
	KeyStatementType type;
	union
	{
		WhileStatement while_s;
	}u;
};
#endif