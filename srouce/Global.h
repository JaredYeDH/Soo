#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
//支持的数据类型
enum Data_Type
{
	Int,
	Char,
	Float,
	String,
	Void,
	Struct,
	Array,
};
//函数解析状态
enum External
{
	Global,		//表示函数外部解析状态
	Local,		//表示函数内部解析状态
};

//语句类型
enum Ex_Statement
{
	Statement_Start, //“｛”
	If_Statement,
	While_Statement,
	For_Statement,
	Continue_Statement,
	Break_Statement,
	Return_Statement
};
//运算符号
enum Operator
{
	Plus,//+
	Minus,//-
};
//标志符号种类
enum TypeCode
{
	T_Int=0, //整型
	T_Char=1,//字符型
	T_Short=2,//短整型
	T_Void=3,//空类型
	T_Ptr=4,//指针
	T_Func=5,//函数
	T_Struct=6,//结构体
	T_String=7,//字符串
	T_Array=8,//数组
	T_Btype=0x000f,//基本类型掩码
};
//寄存器编码
enum Register
{
	REG_EAX=0,
	REG_ECX,
	REG_EDX,
	REG_EBX,
	REG_ESP,
	REG_EBP,
	REG_ESI,
	REG_EDI,
	REG_ANY
};
#define REG_IRET REG_EAX //指定EAX为存放返回值的寄存器
//寻址方式
enum AddressForm
{
	ADDR_OTHER,//寄存器间接寻址
	ADDR_REG=3,//寄存器直接寻址
};
//存储类型
enum StorageType
{
	Soo_Global=0x00f0,//包括整型常量，字符常量，字符串常量，全局变量，函数定义
	Soo_Local=0x00f1,	//栈中变量
	Soo_Valmask=0x00ff,	//存储类型掩码
	Soo_Lval=0x0100,	//左值
};
#endif