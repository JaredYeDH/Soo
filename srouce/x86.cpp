#include "x86.h"
#include "COFF.h"
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

//������д��һ���ֽ�
void CodeGenerate::GenerateByte(char c)
{
	int IndOne;
	IndOne = Ind + 1;
	if (IndOne > COFF_FileSystem::COFF_FileSystemInstance().Section_text->data_allocated)
		COFF_FileSystem::COFF_FileSystemInstance().Section_Realloc(COFF_FileSystem::COFF_FileSystemInstance().Section_text, IndOne);
	COFF_FileSystem::COFF_FileSystemInstance().Section_text->data[Ind] = c;
	Ind = IndOne;
}
//����ָ��ǰ׺
void CodeGenerate::GeneratePrefix(char opcode)
{
	GenerateByte(opcode);
}
//���ɵ��ֽ�ָ��
void CodeGenerate::GenerateOpcode1(char opcode)
{
	GenerateByte(opcode);
}
//����˫�ֽ�ָ��
void CodeGenerate::GenerateOpcode2(char first, char second)
{
	GenerateByte(first);
	GenerateByte(second);
}
//����ָ��Ѱַ��ʽ�ֽ� ModR/M
void CodeGenerate::GenerateModrm(int mod, int sourceOp, int destinationOp, Symbol *symbol, int correlationvalue)
{

}