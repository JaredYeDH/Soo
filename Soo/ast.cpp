//
//  ast.cpp
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "ast.h"
#include "token.h"
using namespace std;

char * string2char(string str)
{
    return const_cast<char *>(str.c_str());
}

string getsign(string choice)
{
	if (choice == "now")
	{
		stringstream s;
		string str;
		s << nodenum;
		s >> str;
		string sign = node + str;
		return sign;
	}
	else if (choice == "next")
	{
		nodenum++;
		stringstream s;
		string str;
		s << nodenum;
		s >> str;
		string sign = node + str;
		return sign;
	}
}

void immediate_ast::codegen()
{
	cout << " " << number << endl;
}

void number_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	//fout << "OPLOAD AL " << number << endl;
	cout << "OPLOAD AL " << number << endl;
}

void array_ast::codegen()
{
	cout << "OPINITLIST " << name<<" ";
	for (int size = 0; size < values.size(); size++)
		cout << values[size] << " ";
	cout << end << endl;
}

void defvariable_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	variable_value->codegen();
	//fout << "OPINIT " << variable_name << " AL" << endl;
	cout << "OPINIT " << variable_name << " AL" << endl;
}

void judge_ast::codegen()
{
	string sign = getsign(choice);
	if (op == "<")
		cout << "JG " << left->number << " " << right->number << " " << sign << endl;
}

void while_ast::codegen()
{
	string sign = getsign("next");
	if (op == "<")
		cout << "JG " << left->number << " " << right->number << " " << sign << endl;
}

void callfunc_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	//fout << "JMP " <<func_name<< endl;
	cout << "JMP " << func_name << endl;
}

void function_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	//fout << func_name << " :" << endl;
	cout << func_name << " :" << endl;
}

void sign_ast::get_sign()
{
	this->sign = getsign(this->choice);
}

void sign_ast::codegen()
{
	cout <<this->sign<< " :" << endl;
}

void end_ast::codegen()
{
	cout << end << endl;
}
