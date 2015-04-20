#ifndef _KEYWORD_H_
#define _KEYWORD_H_
#include "Expression.h"
#include "Block.h"
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