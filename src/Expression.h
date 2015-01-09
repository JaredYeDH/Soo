#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Variable.h"
//��ֵ���ʽ�����νṹ
struct Assign_Tree
{
	char Sign;
	int left;
	Variable_tag right;
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
#endif