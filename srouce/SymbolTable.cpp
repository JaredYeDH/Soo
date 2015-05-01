#include "SymbolTable.h"
#include "Error.h"
//ջ�ĳ�ʼ��
Stack::Stack()
{
	this->Base = new void *;
	if (!this->Base)
	{
		Error error("SymbolTable", "Stack", "Stack base Pointer Memory allocation failure");
		error.ThrowError();
	}
	this->Top = this->Base;
	this->StackSize = 0;
}
//ջ�ĳ�ʼ��
Stack::Stack(int size)
{
	this->Base = new void *;
	if (!this->Base)
	{
		Error error("SymbolTable", "Stack", "Stack base Pointer Memory allocation failure");
		error.ThrowError();
	}
	this->Top = this->Base;
	this->StackSize = size;
}
//ѹջ,������ջ��Ԫ��
void * Stack::Stack_Push(void * value)
{
	if (this->StackSize + 1 <=this->StackSize)
	{

	}
}