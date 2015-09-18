//
//  ast.h
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#ifndef __Soo__ast__
#define __Soo__ast__

#include <iostream>
using namespace std;

char * string2char(string str);

//number
class number_ast
{
public:
    int number;
	number_ast(int num) :number(num){}
	void codegen();
};

//define variable
class defvariable_ast
{
private:
	string variable_name;
	number_ast * variable_value;
public:
	defvariable_ast(string name,number_ast * number) :
		variable_name(name),variable_value(number){}
	void codegen();
};

//binary
class binary_ast
{
private:
	string op;
	number_ast * left, *right;
public:
	binary_ast(string Operator, number_ast *l, number_ast *r) :
		op(Operator), left(l), right(r){}
	void codegen();
};

//if 
class if_ast
{
private:
	string op;
	number_ast * left, *right;
public:
	if_ast(string Operator, number_ast *l, number_ast * r) :
		op(Operator), left(l), right(r){}
	void codegen();
};


//call funciton
class callfunc_ast
{
private:
	string func_name;
public:
	callfunc_ast(string name) :
		func_name(name){}
	void codegen();
};


//function
class function_ast
{
private:
	string func_name;
public:
	function_ast(string name) :
		func_name(name){}
	void codegen();
};
#endif /* defined(__Soo__ast__) */
