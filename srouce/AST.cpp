#include "AST.h"
#include "Global.h"
#include <string>
using namespace std;
//������������
void AST::AST_Variabledec()
{
	Variable_Type variable_type;//��������
	string variable_name;		//��������
	union variable_values		//��������������û��ֵ������Ƕ����������ֵ
	{
		int values;
		char values;
		float values;
		char * values;//string ����
	};
}
//��������
void AST::AST_Arithmetic()
{

}