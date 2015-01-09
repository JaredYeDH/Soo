#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "LexerHead.h"
#include "Expression.h"
/*
����Block
*/
//�ʷ������ַ�������
struct Block_Token
{
	Token This;
	Block_Token *next;
};
//���ṹ��
struct StatementLink
{
	Block_Token * head;//����
};
//����ṹ��
struct Block
{
	bool loading;//�Ƿ��ȡ
	ExpressionType type;//�������
	StatementLink Thestatementlist;//һ�����
	Block *next;//��һ�����
};
//�ʷ������ַ�������
struct TokenNode
{
	Token This;
	TokenNode *next;
};
#endif