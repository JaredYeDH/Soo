#include "x86.h"
using namespace std;
/*
	���������ȫ�ֱ���
*/
int Rsym; //��¼return λ��
int Ind = 0;//ָ���ڴ���ڵ�λ��
int Local;//�ֲ�������ջ�е�λ��
int Func_Begin;//������ʼָ��
int Func_Ret;//�������� �ͷ�ջ�ռ��С
Symbol * SymbolData;//ֻ���ڷ���

void CodeGenerate::GenerateByte(char c)
{
	int IndOne;
	IndOne = Ind + 1;
	if (IndOne>)
}