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