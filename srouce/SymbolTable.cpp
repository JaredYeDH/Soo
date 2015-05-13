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
	this->SymbolPointer->Root = this->SymbolTreeRoot;
}
//�����ż������νṹ���ű�ϵͳ
void Symbol_System::Symbol_Add(Symbol symboldata,External state)
{
	if (state == Global) //ȫ�ֱ���
	{
		if (this->SymbolPointer == this->SymbolTreeRoot->Child) //ʵʱ�ڵ��Ǹ��ڵ�ĵ�һ������
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer->Root;
			symbolnode.Child = NULL;
			this->SymbolPointer = &symbolnode;
		}
		else
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer->Root;
			symbolnode.Child = NULL;
			this->SymbolPointer->SymbolData.Link = new SymbolTable_Node;
			this->SymbolPointer->SymbolData.Link = &symbolnode;
		}
	}
	else //�ֲ�����,SymbolPointer ���ű�ʵʱָ�벻��
	{
		if (this->SymbolPointer->Child == NULL)
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer;
			this->SymbolPointer->Child = new SymbolTable_Node;
			this->SymbolPointer->Child = &symbolnode;
		}
		else
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer;
			this->SymbolPointer->Child->SymbolData.Link = new SymbolTable_Node;
			this->SymbolPointer->Child->SymbolData.Link = &symbolnode;
		}
		
	}
}
//�����Ŵ����νṹ���ű�ϵͳɾ��
void Symbol_System::Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype)
{

}

//���ű��еı�ʶ������
SymbolTable_Node* Symbol_System::Symbol_Search(string symbolname,TypeCode type,Data_Type dtype)
{
	SymbolTable_Node * ErgodicPointer = new SymbolTable_Node;
	ErgodicPointer=SymbolTreeRoot->Child;
	while (ErgodicPointer != NULL)
	{
		if (ErgodicPointer->SymbolData.Name == symbolname&&ErgodicPointer->SymbolData.Type == type&&ErgodicPointer->SymbolData.DType == dtype)
			return ErgodicPointer;
		SymbolTable_Node * ErgodicChildPointer = new SymbolTable_Node;
		ErgodicChildPointer=ErgodicPointer->Child;
		while (ErgodicChildPointer != NULL)
		{
			if (ErgodicPointer->SymbolData.Name == symbolname&&ErgodicPointer->SymbolData.Type == type&&ErgodicPointer->SymbolData.DType == dtype)
				return ErgodicChildPointer;
			ErgodicChildPointer = ErgodicChildPointer->SymbolData.Link;
		}
		ErgodicPointer = ErgodicPointer->SymbolData.Link;
	}
}