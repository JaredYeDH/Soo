#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//���ű�����ṹ���ڵ�
void Symbol_System::Symbol_CreateTree()
{

	this->SymbolTreeRoot->SymbolData.Name = "SymbolSystem_Root";
	this->SymbolTreeRoot->Child = NULL;
	this->SymbolTreeRoot->Root = NULL;
}
//�����ż������νṹ���ű�ϵͳ
void Symbol_System::Symbol_Add(string symbolname, TypeCode type, Data_Type dtype)
{
	SymbolTable_Node *symbolnode;
	symbolnode->SymbolData.Name = symbolname;
	symbolnode->SymbolData.Type = type;
	symbolnode->SymbolData.DType = dtype;
	if (this->SymbolPointer->Child == NULL)
		this->SymbolPointer->Child = symbolnode;
	else
	{
		while (this->SymbolPointer->Child->SymbolData.Link!=NULL)
		{
			this->SymbolPointer = this->SymbolPointer->Child->SymbolData.Link;
		}
		this->SymbolPointer->SymbolData.Link = symbolnode;
	}

}