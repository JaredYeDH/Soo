#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//���ű�����ṹ���ڵ�
void Symbol_System::Symbol_CreateTree()
{

	this->SymbolTreeRoot->SymbolData.Name = "SymbolSystem_Root";
	this->SymbolTreeRoot->Child = new SymbolTable_Node;
	this->SymbolTreeRoot->Child = NULL;
	this->SymbolTreeRoot->Root = NULL;
	this->SymbolPointer = this->SymbolTreeRoot->Child;
}
//�����ż������νṹ���ű�ϵͳ
void Symbol_System::Symbol_Add(Symbol symboldata,External state)
{
	if (state == Global) //ȫ�ֱ���
	{
		SymbolTable_Node *symbolnode;
		symbolnode->SymbolData.Name = symboldata.Name;
		symbolnode->SymbolData.Type = symboldata.Type;
		symbolnode->SymbolData.DType = symboldata.DType;
		if (this->SymbolPointer->Child == NULL)
		{
			this->SymbolPointer->Child = symbolnode;
			symbolnode->Root = this->SymbolPointer;
		}
		else
		{
			SymbolTable_Node Pointer = *this->SymbolPointer;
			while (this->SymbolPointer->Child->SymbolData.Link != NULL)
			{
				this->SymbolPointer = this->SymbolPointer->Child->SymbolData.Link;
			}
			symbolnode->Root = &Pointer;
			this->SymbolPointer->SymbolData.Link = symbolnode;
			this->SymbolPointer = &Pointer; //��ԭʵʱָ��
		}
	}
	else //�ֲ�����
	{

	}
}
//�����Ŵ����νṹ���ű�ϵͳɾ��
void Symbol_System::Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype)
{

}