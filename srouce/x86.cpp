#include "x86.h"
#include "COFF.h"
using namespace std;
/*
	生成所需的全局变量
*/
int Rsym; //记录return 位置
int Ind = 0;//指令在代码节的位置
int Local;//局部变量在栈中的位置
int Func_Begin;//函数开始指令
int Func_Ret;//函数返回 释放栈空间大小
Symbol * SymbolData;//只读节符号

//向代码节写入一个字节
void CodeGenerate::GenerateByte(char c)
{
	int IndOne;
	IndOne = Ind + 1;
	if (IndOne > COFF_FileSystem::COFF_FileSystemInstance().Section_text->data_allocated)
		COFF_FileSystem::COFF_FileSystemInstance().Section_Realloc(COFF_FileSystem::COFF_FileSystemInstance().Section_text, IndOne);
	COFF_FileSystem::COFF_FileSystemInstance().Section_text->data[Ind] = c;
	Ind = IndOne;
}
//生成指令前缀
void CodeGenerate::GeneratePrefix(char opcode)
{
	GenerateByte(opcode);
}
//生成单字节指令
void CodeGenerate::GenerateOpcode1(char opcode)
{
	GenerateByte(opcode);
}
//生成双字节指令
void CodeGenerate::GenerateOpcode2(char first, char second)
{
	GenerateByte(first);
	GenerateByte(second);
}
//生成指令寻址方式字节 ModR/M
void CodeGenerate::GenerateModrm(int mod, int sourceOp, int destinationOp, Symbol *symbol, int correlationvalue)
{

}
//生成4字节操作数，c：4字节操作数
void CodeGenerate::GenerateDword(unsigned int c)
{
	GenerateByte(c);
	GenerateByte(c >> 8);
	GenerateByte(c >> 16);
	GenerateByte(c >> 24);
}
//生成全局符号地址
void CodeGenerate::GenerateAdd32(int Register, Symbol *symbol, int correlationvalue)
{
	GenerateDword(correlationvalue);
}
//将操作数operand加载到寄存器Register中
void CodeGenerate::GenerateLoad(int correlationvalue, Operand * operand)
{
	int Register, Value, V;
	Data_Type Type;
	Register = operand->Register;
	Value = operand->value;
	Type = operand->type;
	V = Register&Soo_Valmask;
	if (Register&Soo_Lval) //是左值
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
//将寄存器Register中的值存入操作数operand中
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