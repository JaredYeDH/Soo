#include "AST.h"
#include "Global.h"
#include <string>
#include "API.h"
using namespace std;
//��������
void AST::AST_Variabledec(Variable variable)
{
	
	//�����﷨������
	Tree AST_VariabledecTree;
	AST_VariabledecTree.Root.Sign = "Variabledec";
	AST_VariabledecTree.Root.token = "";
	AST_VariabledecTree.Left->Sign = "Type";
	AST_VariabledecTree.Left->token = variable.variable_type;
	AST_VariabledecTree.Right->Sign = "Name";
	AST_VariabledecTree.Right->token = variable.variable_name;
	ASyntax_Tree.push(AST_VariabledecTree);
	API::Instance().Pra_Variable.push_back(variable);
}
//��������
void AST::AST_Variabledef()
{

}
//��������
void AST::AST_Arithmetic()
{

}