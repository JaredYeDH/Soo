#include "ParserHead.h"
#include "LexerHead.h"
#include <stack>
#include <string>
using namespace std;
Lexer Lexer_out;//�ʷ������Ľ��
/*
����
*/
//�������ң���֪���ڣ����Ҿ������
Variable_tag *Search(string text, Variable_tag *First)
{
	Variable_tag *test = First->next;
	while (test!= NULL)
	{
		if (test->name == text)
			return test;
	}
}
//�ж��ǲ��Ǳ���
bool isVariable(string Text, Variable_tag *First)
{
	Variable_tag *test = First;
	while (test!= NULL)
	{
		if (test->name == Text)
			return true;
		test = test->next;
	}
	return false;
}
//�ó���ǰ�ʷ��ַ�����ֵ,��ȷ���Ǳ���
int Get_Variable_number(Variable_tag *First)
{
	int number;
	if (Lexer_out.peek(0).isnumber())
	{
		number = Lexer_out.read().getnumber();
	}
	else if (isVariable(Lexer_out.peek(0).gettext(), First))
	{
		number;
		Variable_tag *test = Search(Lexer_out.peek(0).gettext(), First);
		number = test->value.u.int_vlaue;
	}
	Lexer_out.read();
	return number;
}

//���������������У������
void Add_Variable(Variable_tag * &First)
{
	string text;
	Variable_tag *add = First;
	while (add->next != NULL)
	{
		add = add->next;
	}
	Variable_tag *New = new Variable_tag;
	text = Lexer_out.read().gettext();
	New->name = text;
	if (Lexer_out.read().gettext() == "=")
	{
		if (isVariable(Lexer_out.peek(0).gettext(), First))
			New->value = Search(Lexer_out.peek(0).gettext(), First)->value;
		else if (Lexer_out.peek(0).isnumber())
		{
			New->value.u.int_vlaue = Lexer_out.read().getnumber();
			New->value.type = Int_value;
		}
	}
	New->next = NULL;
	add->next = New;
}
//�жϱ���е��Ǳ���������ֵ������
int Judeg_Variable(Variable_tag *First)
{
	if (isVariable(Lexer_out.peek(0).gettext(), First))
	{
		int number = 0;
		number = Search(Lexer_out.peek(0).gettext(), First)->value.u.int_vlaue;
		return number;
	}
	else//(Lexer_out.peek(0).getnumber())
	{
		int number = Lexer_out.read().getnumber();
		return number;
	}
}
/*
		�������ʽ
*/
//�������ʽ���﷨��
int i, sum = 0;
char *str = 0;
//�ж�һ���ַ��Ƿ�Ϊ����
bool isdigit(char c)
{
	if (c - '0' <= 9 && c - '0' >= 0)
		return true;
	else
		return false;
}
Binary_Tree * parse_F(Binary_Tree *&sun);
Binary_Tree * parse_T(Binary_Tree *&sun);
Binary_Tree * parse_E(Binary_Tree *&root);
//����
Binary_Tree * parse_F(Binary_Tree *&sun)
{
	Binary_Tree *L = new Binary_Tree;
	char c = str[i];
	if (isdigit(c)){
		i++;
		L->data = c;
		L->left = NULL;
		L->right = NULL;
		return L;
	}
	if (c == '(')
	{
		i++;
		L = parse_E(sun);
		c = str[i];
		if (c == ')')
		{
			i++;
			return L;
		}
		return L;
	}
	return L;
}
//��
Binary_Tree * parse_T(Binary_Tree *&sun)
{
	Binary_Tree *L = new Binary_Tree;
	L->data = 'T';
	L->left = parse_F(sun);
	L->right = NULL;
	char c = str[i];
	while (c == '*' || c == '/'){
		i++;
		if (L->right == NULL)
		{
			L->right = parse_F(sun);
			L->data = c;
		}
		else
		{
			Binary_Tree * P = new Binary_Tree;
			P->right = parse_F(P);
			P->left = L;
			P->data = c;
			L = P;
		}
		c = str[i];
	}
	return L;
}
//���ʽ
Binary_Tree * parse_E(Binary_Tree *&root)

{
	Binary_Tree *sun = new Binary_Tree;
	sun->data = 'E';
	sun->left = parse_T(sun);
	sun->right = NULL;
	char c = str[i];
	while (c == '+' || c == '-'){
		i++;
		if (sun->right == NULL)
		{
			sun->right = parse_T(sun);
			sun->data = c;
		}
		else
		{
			Binary_Tree *P = new Binary_Tree;
			P->right = parse_E(P);
			P->left = sun;
			P->data = c;
			sun = P;
		}
		c = str[i];
	}
	if (c == '\0')
		return sun;
	return sun;
}
//��������������ʽ����
void post(Binary_Tree * &root, stack<int> s)
{
	int a, b;
	if (root != NULL)
	{
		post(root->left, s);
		post(root->right, s);
		if (s.size() >= 2)
		{
			if (root->data == '+' || root->data == '-' || root->data == '/' || root->data == '*')
			{
				a = s.top() - '0';
				s.pop();
				b = s.top() - '0';
				s.pop();
				if (root->data == '+')
					a = a + b;
				if (root->data == '-')
					a = b - a;
				if (root->data == '*')
					a = a * b;
				if (root->data == '/')
					a = b / a;
				a = a + 48;
				s.push(a);
			}
			else
			{
				if (isdigit(root->data) || root->data == '+' || root->data == '-' || root->data == '/' || root->data == '*')
					s.push(root->data);
			}
		}
		else
		{
			if (isdigit(root->data) || root->data == '+' || root->data == '-' || root->data == '/' || root->data == '*')
				s.push(root->data);
		}
	}
}
//�����������ʽ�﷨�����Ľ��
int BinaryParse()
{
	stack<int> s; //�����������ʽ��ջ
	i = 0;
	Binary_Tree * L = new Binary_Tree;
	Binary_Tree *sun = new Binary_Tree;
	L = parse_E(sun);
	return s.top();
}
/*
		�����жϱ��ʽ
*/
/*
�жϱ��ʽ���﷨�������Ƿ�Ϊ��
���ݷ��ŵ����ȼ���������������ȥ�Ƚ�
*/
//�жϱ��ʽ��<,>,<=,>=1�������
Tree_Judge* G_L_Expreesion(Variable_tag *First)
{
	Tree_Judge *L = new Tree_Judge;
	int number = Judeg_Variable(First);
	L->left = new Tree_Judge;
	L->right = new Tree_Judge;
	L->left->u.data = number;
	Lexer_out.read();
	while (Lexer_out.peek(0).gettext() == "<" || Lexer_out.peek(0).gettext() == ">" || Lexer_out.peek(0).gettext() == "<=" || Lexer_out.peek(0).gettext() == ">=" || Lexer_out.peek(0).gettext() == "!=")
	{
		char *c;
		const int len = Lexer_out.peek(0).gettext().length();
		c= new char[len + 1];
		strcpy(c, Lexer_out.read().gettext().c_str());
		L->u.sign = c;
		number=Judeg_Variable(First);
		L->right->u.data = number;
	}
	L->right->right = NULL;
	L->right->left = NULL;
	L->left->right = NULL;
	L->left->left = NULL;
	return L;

}
//�жϱ��ʽ��&&2�������
Tree_Judge * AND_Expreesion(Variable_tag *First)
{
	Tree_Judge *L = new Tree_Judge;
	L= G_L_Expreesion(First);
	L= NULL;
	while (Lexer_out.peek(0).gettext() == "&&")
	{
		char *c;
		const int len = Lexer_out.peek(0).gettext().length();
		c = new char[len + 1];
		strcpy(c, Lexer_out.read().gettext().c_str());
		L->u.sign = c;
		Lexer_out.read();
		L->right = G_L_Expreesion(First);
	}
	return L;
}
//�жϱ��ʽ��||3�������
Tree_Judge * OR_Expreesion(Variable_tag *First)
{
	Tree_Judge *out = new Tree_Judge;
	out= AND_Expreesion(First);
	out->right= NULL;
	out->left = NULL;
	while (Lexer_out.peek(0).gettext() == "||")
	{
		char *c;
		const int len = Lexer_out.peek(0).gettext().length();
		c = new char[len + 1];
		strcpy(c, Lexer_out.read().gettext().c_str());
		out->u.sign = c;
		out->right = AND_Expreesion(First);
	}
	return out;
}
//��������жϱ��ʽ����Ҫ��ջ
stack<Tree_Judge *> Expreesion_Stack;
//��������жϱ��ʽ���﷨��
void Postinorder_Expreesion(Tree_Judge * &Judeg_Expreesion)
{
	if (Judeg_Expreesion != NULL)
	{
		Postinorder_Expreesion(Judeg_Expreesion->left);
		Postinorder_Expreesion(Judeg_Expreesion->right);
		if (Expreesion_Stack.size() >= 2)
		{
			string s(Judeg_Expreesion->u.sign);
			if (s=="<") //��ջ���ж�<
			{
				int one, two;
				one = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				two = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				if (two < one)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_Stack.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_Stack.push(statue);
				}
			}
			if (Judeg_Expreesion->u.sign == ">") //��ջ���ж�>
			{
				int one, two;
				one = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				two = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				if (one > two)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_Stack.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_Stack.push(statue);
				}
			}
			if (Judeg_Expreesion->u.sign == "<=")
			{
				int one, two;
				one = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				two = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				if (one <= two)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_Stack.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_Stack.push(statue);
				}
			}
			if (Judeg_Expreesion->u.sign == ">=")
			{
				int one, two;
				one = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				two = Expreesion_Stack.top()->u.data;
				Expreesion_Stack.pop();
				if (one >= two)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_Stack.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_Stack.push(statue);
				}
			}
		}
		else
			Expreesion_Stack.push(Judeg_Expreesion);
	}
}
//�жϱ��ʽ��BOOLֵ
bool  Bool_Expreesion(Variable_tag *First)
{
	bool Judge_Ex;
	Tree_Judge * Judge_Expression = new Tree_Judge;
	Judge_Expression=OR_Expreesion(First);
	Postinorder_Expreesion(Judge_Expression);
	Judge_Ex = Judge_Expression->u.bool_output;
	return Judge_Ex;
}
/*
	���ʽ�ľ��庯��
*/
void Assign_Expression(Variable_tag *First)
{
	if (Search(Lexer_out.peek(0).gettext(),First)->value.type == Int_value)
	{
		Assign_Tree *Assign = new Assign_Tree;
		Assign->left = Search(Lexer_out.read().gettext(),First)->value;
		Binary_Tree *Binary = new Binary_Tree;
		Assign->right = parse_E(Binary);
		Assign->left.u.int_vlaue = BinaryParse();
	}
}
/*
	����
*/
//ִ������
void Block_run(Variable_tag *First)
{
	Block * StatementList = new Block;
	if (Lexer_out.peek(0).gettext() == "{")
	{
		Lexer_out.read();
		//�Ǹ�ֵ���ʽ
		if (Lexer_out.peek(1).gettext() == "=")
		{
			//������ֵ
			if (isVariable(Lexer_out.peek(0).gettext(),First))
			{
				Assign_Expression(First);
			}
		}
	}
}
/*
	�ؼ���
*/
//Print�ؼ��֣����������ֵ
void Printvalue(Variable_tag *example)
{
	switch (example->value.type)
	{
	case Int_value: //������int��
	{
						int number;
						number = example->value.u.int_vlaue;
						cout << number;
	}
	default:
		break;
	}
}
//�ж��ǲ��ǹؼ���
bool IsKeyword(string s)
{
	if (s == "while")
		return true;
	else if (s == "print")
		return true;
	else
		return false;
}
//��ʲô�ؼ���
void IswhatKeyword(string text, Variable_tag *First)
{
	Statement_tag goal;
	string test;
	if (text == "while") //�ؼ�����While
	{
		Lexer_out.read();
		goal.type = WHILE_STATEMENT;
		test= Lexer_out.peek(0).gettext();
		if(test[1]=='(')
		{
			Lexer_out.read();
			//ת���жϱ��ʽ����ֵ
			for (;;)
			{
				if (Bool_Expreesion(First))
					break;
				else
					Block_run(First);//����ִ������
			}
		}
	}
	else if (text == "print") //�ؼ�����Print
	{
		string test = Lexer_out.peek(0).gettext();
		if (isVariable(test,First))
		{
			Variable_tag *example = Search(text,First);
			Printvalue(example);
		}
	}
}
//�﷨����
void Parser()
{
	Variable_tag *First = new Variable_tag;//ȫ�ֱ��������ͷָ��
	First->next= NULL;
	string text;
	while (Queue.size() != 0)
	{
		text = Lexer_out.peek(0).gettext();
		if (text == "\\n")
		{
			Lexer_out.read();
			text = text = Lexer_out.peek(0).gettext();
		}
		if (IsKeyword(text))//�ǹؼ���
			IswhatKeyword(text,First);
		else if (Lexer_out.peek(1).gettext() == "=") //��ֵ���
		{
			Add_Variable(First);
		}
		else if (isVariable(text,First)) //�Ǳ���
		{

		}
		
	}
}
int main()
{
	int linenumber = 0;
	Token t;
	ifstream infile("string.txt");
	string line;
	while (getline(infile, line))
	{

		linenumber++;
		Lexer_out.readline(line, linenumber);
	}
	Parser();
	return 0;
}