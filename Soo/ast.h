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
#include <vector>
#include <string>
using namespace std;

char * string2char(string str);
string getsign(string choice);
//immediate number
class immediate_ast
{
public:
    int number;
	immediate_ast(int num) :number(num){}
	void codegen();
};

//number
class number_ast
{
public:
	int number;
	number_ast(int num) :number(num){}
	void codegen();
};

//array
class array_ast
{
public:
	string name;
	vector<int> values;
	int size;
	string end;
	array_ast(string array_name,vector<int> array_values, int array_size) :
		name(array_name),values(array_values), size(array_size),end("$"){}
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

//judge
class judge_ast
{
private:
	string choice;
	string op;
	immediate_ast * left, *right;
public:
	judge_ast(string Operator, immediate_ast *l, immediate_ast * r,string sign_choice) :
		op(Operator), left(l), right(r),choice(sign_choice){}
	void codegen();
};

//if 
class if_ast
{
private:
	string op;
	immediate_ast * left, *right;
public:
	if_ast(string Operator, immediate_ast *l, immediate_ast * r) :
		op(Operator), left(l), right(r){}
	void codegen();
};

//while
class while_ast
{
private:
	string op;
	immediate_ast *left, *right;
public:
	while_ast(string Operator, immediate_ast *l, immediate_ast *r) :
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

//label address
class sign_ast
{
private:
	string sign;
	string choice;
public:
	sign_ast(string str) :
		choice(str){}
	void get_sign();
	void codegen();
};

//end label
class end_ast
{
private:
	string end;
public:
	end_ast(string str) :
		end(str){}
	void codegen();
};
#endif /* defined(__Soo__ast__) */
