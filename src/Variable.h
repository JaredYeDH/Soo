/*
		�﷨������������
*/
#ifndef _VARIABLE_H_
#define _VARIABLE_H_
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
//�������ң���֪���ڣ����Ҿ������
Variable_tag *Search(string text, Variable_tag *First);
//�ж��ǲ��Ǳ���
bool isVariable(string Text, Variable_tag *First);
//�ó���ǰ�ʷ��ַ�����ֵ,��ȷ���Ǳ���
int Get_Variable_number(Variable_tag *First);
//���������������У������
void Add_Variable(Variable_tag * &First);
//�жϱ���е��Ǳ���������ֵ������
int Judeg_Variable(Variable_tag *First);
//���غ��� Judeg_Variable,����������ַ�ֵ��Ѱ�ұ�����ֵ
int Judeg_Variable(Variable_tag *First, string search);
#endif