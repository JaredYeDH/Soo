#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//������ѹ�����ջ
void Symbol_System::Symbol_DirectPush(stack<Symbol> * stack, int number, Data_Type  type, int correlation_value)
{
	Symbol s;
	s.Number = number;
	s.Type = type;
	s.Correlation_value = correlation_value;
	s.Next = NULL;
	stack->push(s);
}
//������ѹ�����ջ����̬�ж�ȫ�ֻ�ֲ�
Symbol *Symbol_System::Symbol_Push(int number, Data_Type type, int memory_type, int correlation_value)
{
	stack<Symbol> *s;
	if (Local_Stack.empty())
		s = &Global_Stack;
	else
		s = &Local_Stack;
	Symbol_DirectPush(s, number, type, correlation_value);
}
//���������ŷ���ȫ�ַ��ű���
Symbol * Symbol_System::Symbol_FunctionPush(int number, Data_Type * type)
{

}
//�ѱ���������ű���
Symbol *Symbol_System::Symbol_VariablePush(Data_Type type, int Register, int number, int address)
{
	if ((Register &M_Valmask) == M_Local)
		Symbol_Push(number,type);
}