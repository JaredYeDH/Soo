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
	//�����﷨������
	Tree AST_VariabledecTree;
	AST_VariabledecTree.Root.Sign = "Variabledec";
	AST_VariabledecTree.Root.token = NULL;
	AST_VariabledecTree.Left->Sign = "dec";
	AST_VariabledecTree.Left->token = NULL;
	AST_VariabledecTree.Left->Left->Sign = "type";
	AST_VariabledecTree.Left->Left->
}
//��������
void AST::AST_Arithmetic()
{

}