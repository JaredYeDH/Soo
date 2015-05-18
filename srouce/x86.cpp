#include "x86.h"
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

void CodeGenerate::GenerateByte(char c)
{
	int IndOne;
	IndOne = Ind + 1;
	if (IndOne>)
}