#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "LexerHead.h"
#include "Expression.h"
/*
	����Block
*/
//���ṹ��
struct StatementLink
{
	Token This;
	StatementLink *next;
};
//����ṹ��
struct Block
{
	bool loading;//�Ƿ��ȡ
	ExpressionType type;//�������
	StatementLink *Thestatementlist;//һ�����
	Block *next;//��һ�����
};
//�ʷ������ַ�������
struct TokenNode
{
	Token This;
	TokenNode *next;
};
#endif