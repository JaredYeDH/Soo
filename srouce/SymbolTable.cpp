#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//������ѹ�����ջ
Symbol *Symbol_System::Symbol_DirectPush(stack<Symbol> * stack, int number, Symbol_Type  type, int correlation_value)
{
	Symbol s, *Ref;
	s.Number = number;
	s.Type = type;
	s.Correlation_value = correlation_value;
	s.Next = NULL;
	stack->push(s);
	Ref = &s;
}
//������ѹ�����ջ����̬�ж�ȫ�ֻ�ֲ�
Symbol *Symbol_System::Symbol_Push(int number, Symbol_Type type, int memory_type, int correlation_value)
{
	Symbol *Ps, **PPs;
	TKWord * Word;
	stack<Symbol> *s;
	if (Local_Stack.empty())
		s = &Global_Stack;
	else
		s = &Local_Stack;
	Ps=Symbol_DirectPush(s, number, type, correlation_value);
	Ps->Type = type;
	if (number&M_Struct)
	{
		//���µ��� struct���� identifier �ֶ�
		Word = TKArrayTable.data[(number&~M_Struct)];
		if (number&M_Struct)
			PPs = &Word->symbol_struct;
		else
			PPs = &Word->symbol_ID;
		Ps->Prev_token = *PPs;
		*PPs = Ps;
	}
	return Ps;
}
//���������ŷ���ȫ�ַ��ű���
Symbol * Symbol_System::Symbol_FunctionPush(int number, Symbol_Type type)
{
	Symbol *S=NULL, **Ps=NULL;
	S = Symbol_DirectPush(&Global_Stack, number, type,0);
	Ps = &(TKArrayTable.data[number])->symbol_ID;
	while (Ps != NULL)
		Ps = &(*Ps)->Prev_token;
	S->Prev_token = NULL;
	*Ps = S;
	return S;
}
//�ѱ���������ű���
Symbol *Symbol_System::Symbol_VariablePush(Symbol_Type type, int memory_type, int number, int address)
{
	Symbol * Sym = NULL;
	if ((memory_type&M_Valmask) == M_Local) //�ֲ�����
		Sym = Symbol_Push(number, type, memory_type, address);
	else
		Sym = Symbol_Search(memory_type);
}
//��ʶ������ 
Symbol * Symbol_System::Symbol_Search(int number)
{
	if (number >= TKArrayTable.size())
		return NULL;
	else
		return TKArrayTable.data[number]->symbol_ID;
}