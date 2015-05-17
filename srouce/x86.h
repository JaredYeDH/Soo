/*
	生成x86机器语言
*/
#pragma once
#ifndef _X86_H
#define _X86_H
#include "Global.h"
#include "SymbolTable.h"
//操作树存储结构
struct Operand
{
	Data_Type type;//数据类型
	unsigned short Register;//寄存器或存储类型
	int value;//常量值
	struct Symbol * symbol;//关联符号
};
//生成x86机器语言
class CodeGenerate
{
public:
	//生成通用指令
	void GenerateByte(char c);//向代码节写入一个字节
	void GeneratePrefix(char opcode);//生成指令前缀
	void GenerateOpcode1(char opcode);//生成单字节指令
	void GenerateOpcode2(char first, char second);//生成双字节指令
	void GenerateModrm(int mod, int sourceOp, int destinationOp, Symbol *symbol, int correlationvalue);//生成指令寻址方式字节 ModeR/M
	void GenerateDword(unsigned int c);//生成4字节操作数
	void GenerateAdd32(int Register, Symbol *symbol, int correlationvalue);//生成全局符号地址，并增加COFF重定位记录
	//生成数据传送指令
	void GenerateLoad(int Register, Operand *operand);//将操作数operand加载到寄存器Register的中
	void GenerateStore(int Register, Operand *operand);//将寄存器Register中的值存入操作数operand中
};
#endif