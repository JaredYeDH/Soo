#include "ParserHead.h"
#include "Variable.h"
#include "Expression.h"
#include"Block.h"
#include "Keyword.h"
#include "LexerHead.h"
#include <stack>
#include <string>
using namespace std;
/*
����
*/
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
//���غ��� Judeg_Variable,����������ַ�ֵ��Ѱ�ұ�����ֵ
int Judeg_Variable(Variable_tag *First, string search)
{
	if (isVariable(search, First))
	{
		int number = 0;
		number = Search(search, First)->value.u.int_vlaue;
		return number;
	}
}
//�ж��ǲ��Ǳ���
bool isVariable(string Text, Variable_tag *First)
{
	Variable_tag *test = First;
	while (test != NULL)
	{
		if (test->name == Text)
			return true;
		test = test->next;
	}
	return false;
}
//�������ң���֪���ڣ����Ҿ������
Variable_tag *Search(string text, Variable_tag *First)
{
	Variable_tag *test = First->next;
	while (test != NULL)
	{
		if (test->name == text)
			return test;
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
Binary_Tree * parse_F(Binary_Tree *&sun, TokenNode *&HeadToken);
Binary_Tree * parse_T(Binary_Tree *&sun, TokenNode *&HeadToken);
Binary_Tree * parse_E(Binary_Tree *&root, TokenNode *&HeadToken);
//����
Binary_Tree * parse_F(Binary_Tree *&sun, TokenNode *&HeadToken)
{
	Binary_Tree *L = new Binary_Tree;
	char c = HeadToken->This.gettext()[0];
	if (isdigit(c)){
		i++;
		L->data = c;
		HeadToken = HeadToken->next;
		L->left = NULL;
		L->right = NULL;
		return L;
	}
	if (c == '(')
	{
		i++;
		L = parse_E(sun,HeadToken);
		c = HeadToken->This.gettext()[0];
		if (c == ')')
		{
			HeadToken = HeadToken->next;
			i++;
			return L;
		}
		return L;
	}
	return L;
}
//��
Binary_Tree * parse_T(Binary_Tree *&sun, TokenNode *&HeadToken)
{
	Binary_Tree *L = new Binary_Tree;
	L->data = 'T';
	L->left = parse_F(sun,HeadToken);
	L->right = NULL;
	char c = HeadToken->This.gettext()[0];
	while (c == '*' || c == '/'){
		i++;
		if (L->right == NULL)
		{
			L->right = parse_F(sun,HeadToken);
			L->data = c;
			HeadToken = HeadToken->next;
		}
		else
		{
			Binary_Tree * P = new Binary_Tree;
			P->right = parse_F(P,HeadToken);
			P->left = L;
			P->data = c;
			HeadToken = HeadToken->next;
			L = P;
		}
		c = str[i];
	}
	return L;
}
//���ʽ
Binary_Tree * parse_E(Binary_Tree *&root, TokenNode * &HeadToken)

{
	Binary_Tree *sun = new Binary_Tree;
	sun->data = 'E';
	sun->left = parse_T(sun,HeadToken);
	sun->right = NULL;
	char c = HeadToken->This.gettext()[0];
	while (c == '+' || c == '-'){
		i++;
		if (sun->right == NULL)
		{
			sun->right = parse_T(sun,HeadToken);
			sun->data = c;
			HeadToken = HeadToken->next;
		}
		else
		{
			Binary_Tree *P = new Binary_Tree;
			P->right = parse_E(P,HeadToken);
			P->left = sun;
			P->data = c;
			HeadToken = HeadToken->next;
			sun = P;
		}
		c = HeadToken->This.gettext()[0];
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
int BinaryParse(TokenNode * &HeadToken)
{
	stack<int> s; //�����������ʽ��ջ
	i = 0;
	Binary_Tree * L = new Binary_Tree;
	Binary_Tree *sun = new Binary_Tree;
	L = parse_E(sun,HeadToken);
	post(L,s);
	return s.top();
}
/*
	�����жϱ��ʽ
*/
/*
�жϱ��ʽ���﷨�������Ƿ�Ϊ��
���ݷ��ŵ����ȼ���������������ȥ�Ƚ�
*/
//�жϱ��ʽ�ַ�������ṹ��
struct Expreesion_Node
{
	bool statue;
	Token This;
	Expreesion_Node *next;
};
//�жϱ��ʽ��<,>,<=,>=1�������
Tree_Judge* G_L_Expreesion(Variable_tag *First, Expreesion_Node *&Bool_Expreesion)
{
	int number;
	Tree_Judge *L = new Tree_Judge;
	string test =Bool_Expreesion->next->This.gettext();
	if (isVariable(test, First))//����Ǳ���
	{
		number = Judeg_Variable(First, test);

	}
	else
	{
		number = Bool_Expreesion->next->This.getnumber();
	}
	Bool_Expreesion = Bool_Expreesion->next;
	L->left = new Tree_Judge;
	L->right = new Tree_Judge;
	L->left->u.data = number;
	test = Bool_Expreesion->next->This.gettext();
	while (test == "<" || test == ">" || test == "<=" || test == ">=" || test == "!=")
	{
		char *c;
		const int len = test.length();
		c = new char[len + 1];
		strcpy(c, test.c_str());
		L->u.sign = c;
		Bool_Expreesion = Bool_Expreesion->next;
		test = Bool_Expreesion->next->This.gettext();
		if (isVariable(test, First))//����Ǳ���
		{

			number = Judeg_Variable(First, test);
		}
		else
		{
			number = Bool_Expreesion->next->This.getnumber();
		}
		Bool_Expreesion = Bool_Expreesion->next;
		L->right->u.data = number;
	}
	L->right->right = NULL;
	L->right->left = NULL;
	L->left->right = NULL;
	L->left->left = NULL;
	return L;

}
//�жϱ��ʽ��&&2�������
Tree_Judge * AND_Expreesion(Variable_tag *First, Expreesion_Node *&Bool_Expreesion)
{
	Tree_Judge *L = new Tree_Judge;
	L = G_L_Expreesion(First, Bool_Expreesion);
	string test = Bool_Expreesion->next->This.gettext();
	while (test == "&&")
	{
		Tree_Judge *P = new Tree_Judge;
		P->left = L;
		char *c;
		const int len = test.length();
		c = new char[len + 1];
		strcpy(c, test.c_str());
		P->u.sign = c;
		Bool_Expreesion = Bool_Expreesion->next;
		P->right = G_L_Expreesion(First, Bool_Expreesion);
		test = Bool_Expreesion->This.gettext();
		L = P;
	}
	return L;
}
//�жϱ��ʽ��||3�������
Tree_Judge * OR_Expreesion(Variable_tag *First, Expreesion_Node *&Bool_Expreesion)
{
	Tree_Judge *out = new Tree_Judge;
	out = AND_Expreesion(First, Bool_Expreesion);
	string test = Bool_Expreesion->next->This.gettext();
	while (test == "||")
	{
		Tree_Judge *P = new Tree_Judge;
		P->left= out;
		char *c;
		const int len = test.length();
		c = new char[len + 1];
		strcpy(c, test.c_str());
		P->u.sign = c;
		Bool_Expreesion = Bool_Expreesion->next;
		P->right = AND_Expreesion(First, Bool_Expreesion);
		test = Bool_Expreesion->This.gettext();
		out = P;
	}
	return out;
}
//��������жϱ��ʽ����Ҫ��ջ
/*
Ϊ���������3��ջ�����������ڵ�1���ȼ����������Bool���
*/
stack<Tree_Judge *> Expreesion_StackFirst;
stack<Tree_Judge *> Expreesion_StackSec;
//��������жϱ��ʽ���﷨��
void Postinorder_Expreesion(Tree_Judge * &Judeg_Expreesion)
{
	if (Judeg_Expreesion != NULL)
	{
		Postinorder_Expreesion(Judeg_Expreesion->left);
		Postinorder_Expreesion(Judeg_Expreesion->right);
		if (Expreesion_StackFirst.size() >= 2)
		{
			string s(Judeg_Expreesion->u.sign);
			if (s == "<") //��ջ���ж�<
			{
				int one, two;
				one = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				two = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				if (two<one)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
			else if (s== ">") //��ջ���ж�>
			{
				int one, two;
				one = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				two = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				if (two >one )
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
			else if (s== "<=")
			{
				int one, two;
				one = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				two = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				if (two <= one)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
			else if (s== ">=")
			{
				int one, two;
				one = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				two = Expreesion_StackFirst.top()->u.data;
				Expreesion_StackFirst.pop();
				if (two>= one)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
		}
		else if (Expreesion_StackSec.size() >= 2)
		{
			string s(Judeg_Expreesion->u.sign);
			if (s== "||")
			{
				bool one, two;
				one = Expreesion_StackSec.top()->u.bool_output;
				Expreesion_StackSec.pop();
				two = Expreesion_StackSec.top()->u.bool_output;
				Expreesion_StackSec.pop();
				if (one || two)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
			else if (s == "&&")
			{
				bool one, two;
				one = Expreesion_StackSec.top()->u.bool_output;
				Expreesion_StackSec.pop();
				two = Expreesion_StackSec.top()->u.bool_output;
				Expreesion_StackSec.pop();
				if (one && two)
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 1;
					Expreesion_StackSec.push(statue);
				}
				else
				{
					Tree_Judge *statue = new Tree_Judge;
					statue->type = Bool;
					statue->u.bool_output = 0;
					Expreesion_StackSec.push(statue);
				}
			}
		}
		else
			Expreesion_StackFirst.push(Judeg_Expreesion);
	}
}
//�õ��жϱ��ʽ���ַ���
void Get_BoolExpression(Expreesion_Node * &Bool_Expreesion)
{
	Expreesion_Node *P = new Expreesion_Node;
	P = Bool_Expreesion;
	Bool_Expreesion->statue = true;
	string test = Lexer_out.peek(0).gettext();
	while (test[0] != ')')
	{
		Expreesion_Node *Q = new Expreesion_Node;
		Q->This = Lexer_out.read();
		test = Q->This.gettext();
		P->next = Q;
		P = Q;
	}
}
//�жϱ��ʽ��BOOLֵ
bool  Bool_Expreesion(Variable_tag *First)
{
	//����ͷָ��
	Expreesion_Node *Bool_Expreesion = new Expreesion_Node;//�����жϱ��ʽ�е��ַ���

	if (Bool_Expreesion->statue != true)
	{
		Get_BoolExpression(Bool_Expreesion);
	}
	Expreesion_Node *P = new Expreesion_Node;
	P = Bool_Expreesion;
	bool Judge_Ex;
	Tree_Judge * Judge_Expression = new Tree_Judge;//�����жϱ��ʽ����
	Judge_Expression = OR_Expreesion(First, P);//�����������ʽ�����ж�
	Postinorder_Expreesion(Judge_Expression);//�����жϱ��ʽ���﷨������
	Judge_Ex = Expreesion_StackSec.top()->u.bool_output;//������Ľ������bool�жϵ�ֵ
	return Judge_Ex;
}
/*
		���ʽ�ľ��庯��
*/

/*
	����
*/

//ִ������
void Block_run(Variable_tag *First)
{
	string text = Lexer_out.peek(0).gettext();
	if (text == "\\n")
		Lexer_out.read();/* ��ȡ���з���\n*/
	Block *Block_Expression=new Block;
	/*
		���û�ж��������L��Token ���뵽�����������,
	*/
	if (Block_Expression->loading != true)
	{
		if (Lexer_out.peek(0).gettext() == "{")
		{
			Lexer_out.read();//��ȡ"{"
			Block *Dirty = new Block;
			Block_Expression = Dirty;
			Dirty->loading = true;
			while (Lexer_out.read().gettext() != "}")
			{
				Block *Dirtysun = new Block;
				//����Ǹ�ֵ���ʽ
				if (Lexer_out.peek(1).gettext() == "=")
				{
					StatementLink *Link = new StatementLink;
					Dirtysun->type = ASSIGN_EXPRESSION;
					Link->head = new Block_Token;
					Link->head->This = Lexer_out.read();
					while (Lexer_out.peek(0).gettext() != "\\n")
					{
						Block_Token *Site = new Block_Token;
						Site->This = Lexer_out.read();
						Site->next = NULL;
						Link->head->next=Site;
						Link->head = Link->head->next;
					}
					if (Lexer_out.peek(0).gettext() != "\\n")
						Lexer_out.read();//��ȡ\n
					Dirtysun->Thestatementlist = *Link;
					Dirty = Dirtysun;
					Dirty = Dirty->next;
				}

			}
			Lexer_out.read();//��ȡ"}"
		}
	}
	/*
		ִ������
	*/
	while (Block_Expression != NULL)
	{
		if (Block_Expression->type = ASSIGN_EXPRESSION)//����ֵ���
		{
			Assign_Tree *Assign = new Assign_Tree;
			Assign->Sign = '=';
			Assign->right = *Search(Block_Expression->Thestatementlist.head->This.gettext() , First);
			//��ȡ��ֵ����"="�ĺ��沿��
			TokenNode *HeadToken = new TokenNode;
			TokenNode *SiteToken = new TokenNode;
			SiteToken = HeadToken;
			while (Block_Expression->Thestatementlist.head->next != NULL)
			{
				SiteToken->This = Block_Expression->Thestatementlist.head->This;
				SiteToken= SiteToken->next;
			}
			Assign->left = BinaryParse(SiteToken);
			Assign->right.value.u.int_vlaue = Assign->left;
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
		test = Lexer_out.peek(0).gettext();
		if (test[0] == '(')
		{
			Lexer_out.read();
			//ת���жϱ��ʽ����ֵ
			for (;;)
			{
				if (!Bool_Expreesion(First))
					break;
				else
					Block_run(First);//����ִ������
			}
		}
	}
	else if (text == "print") //�ؼ�����Print
	{
		string test = Lexer_out.peek(0).gettext();
		if (isVariable(test, First))
		{
			Variable_tag *example = Search(text, First);
			Printvalue(example);
		}
	}
}
//�﷨����
void Parser()
{
	Variable_tag *First = new Variable_tag;//ȫ�ֱ��������ͷָ��
	First->next = NULL;
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
			IswhatKeyword(text, First);
		//��ʼ����ֵ
		else if (Lexer_out.peek(1).gettext() == "=") //��ֵ���
		{
			Add_Variable(First);
		}
		else if (isVariable(text, First)) //�Ǳ���
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