//
//  ast.cpp
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "ast.h"
#include "token.h"
using namespace std;

char * string2char(string str)
{
    return const_cast<char *>(str.c_str());
}

void number_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	//fout << "OPLOAD AL " << number << endl;
	cout << "OPLOAD AL " << number << endl;
}

void defvariable_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	variable_value->codegen();
	//fout << "OPINIT " << variable_name << " AL" << endl;
	cout << "OPINIT " << variable_name << " AL" << endl;
}

void if_ast::codegen()
{
	//ofstream fout(string2char(token::outfile));
	left->codegen();
	if (op == "<" || op == ">")
		//fout << "CMP AL " << right->number << endl;
		cout << "CMP AL " << right->number << endl;
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
