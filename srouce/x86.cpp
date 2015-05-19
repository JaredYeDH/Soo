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
//����4�ֽڲ�������c��4�ֽڲ�����
void CodeGenerate::GenerateDword(unsigned int c)
{
	GenerateByte(c);
	GenerateByte(c >> 8);
	GenerateByte(c >> 16);
	GenerateByte(c >> 24);
}
//����ȫ�ַ��ŵ�ַ
void CodeGenerate::GenerateAdd32(int Register, Symbol *symbol, int correlationvalue)
{
	GenerateDword(correlationvalue);
}
//��������operand���ص��Ĵ���Register��
void CodeGenerate::GenerateLoad(int correlationvalue, Operand * operand)
{
	int Register, Value, V;
	Data_Type Type;
	Register = operand->Register;
	Value = operand->value;
	Type = operand->type;
	V = Register&Soo_Valmask;
	if (Register&Soo_Lval) //����ֵ
	{
		if ((Type&T_Btype) == T_Char)
			GenerateOpcode2(0x0f, 0xbe);
		else if ((Type&T_Btype) == T_Short)
			GenerateOpcode2(0x0f, 0xbf);
		else
			GenerateOpcode1(0x8b);
	}
	else
	{
		if (V == Soo_Global)
		{
			GenerateOpcode1(0xb8 + correlationvalue);
			GenerateAdd32(Register, operand->symbol, Value);
		}
		else if (V == Soo_Local)
		{
			GenerateOpcode1(0x8d);
		}
	}
}
//���Ĵ���Register�е�ֵ���������operand��
void CodeGenerate::GenerateStore(int Register, Operand *operand)
{
	int Register, ByteType;
	Register = operand->Register&Soo_Valmask;
	ByteType = operand->type&T_Btype;
	if (ByteType == T_Short)
		GeneratePrefix(0x66);
	if (ByteType == T_Char)
		GenerateOpcode1(0x88);
	else
		GenerateOpcode1(0x89);
}