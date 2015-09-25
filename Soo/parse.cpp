//
//  parse.cpp
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include "parse.h"
#include "ast.h"
#include "global.h"
using namespace std;

//static 
int parse::index = 0;

int parse::string2int(string str)
{
    return atoi(str.c_str());
}

bool parse::judge_op(string token)
{
	if (token == "+" || token == "-" || token == "*" || token == "/")
		return true;
	else
		return false;
}

bool parse::judge_variable(string token)
{
	if (symbol_search(token))
		return true;
	else
		return false;
}

bool parse::lowlevel(string token,string top)
{
	if (token == "*" || token == "/"&&token == "+" || token == "-")
		return false;
	else
		return true;
}

int parse::operation(int num1, int num2,string op)
{
	int out;
	if (op == "+")
		out = num1 + num2;
	else if (op == "-")
		out = num1 - num2;
	else if (op == "*")
		out = num1 * num2;
	else if (op == "/")
		out = num1 / num2;
	return out;
}

int parse::binary_lsy()
{
	stack<int> num;
	stack<string> op;
	while (codestream[index] != "\n")
	{
		string token = codestream[index];
		if (judge_op(token))
		{
			if (op.size() == 0)
				op.push(token);
			else if (lowlevel(token, op.top()))
			{
				int number2 = num.top();
				num.pop();
				int number1 = num.top();
				num.pop();
				string operand = op.top();
				int out = operation(number1, number2, operand);
				num.push(out);
			}
			else
			{
				op.push(token);
			}
		}
		else if (judge_variable(token))
		{
			int variable_value = symbol_getvalue(token);
			num.push(variable_value);
		}
		else //number
		{
			int number = string2int(token);
			num.push(number);
		}
		index++;
	}
	while (op.size() != 0)
	{
		int number2 = num.top();
		num.pop();
		int number1 = num.top();
		num.pop();
		string operand = op.top();
		op.pop();
		int out = operation(number1, number2, operand);
		num.push(out);
	}
	return num.top();
}

int parse::getvalue(string name)
{
	int value;
	if (judge_variable(name))
		value = symbol_getvalue(name);
	else
		value = string2int(name);
	return value;
}
//build syntax tree
void parse::build_ast()
{
	for (index = 0; index < codestream.size(); index++)
	{
		string token = codestream[index];
		//statement or define variable
		if (token == "var")
		{
			index++;
			parse_defvar();
		}
		//binary expreesion
		else if (judge_variable(token))
		{
			string variable_name = codestream[index];
			index++;
			if (codestream[index] == "=")
				parse_binary(variable_name);

		}
		else if (token == "def")
		{
			index++;
			parse_func();
		}
		else if (codestream[index] == "\n")
			continue;
	}
}
//statement or define variable
void parse::parse_defvar()
{
	string type = codestream[index];
	index++;
	string name = codestream[index];
	index++;
	//array
	if (codestream[index] == "[")
	{
		index++;
		int size = string2int(codestream[index]);
		index++;
		// token "]"
		index++;
		//define
		if (codestream[index] == "=")
		{
			index++;
			if (codestream[index] == "{")
			{
				index++;
				vector<int> num;
				while (codestream[index] != "}")
				{
					if (codestream[index] == ",")
					{
						index++;
						continue;
					}
					else
						num.push_back(string2int(codestream[index]));
					index++;
				}
				symbol_insert_intarray(name, num);
				array_ast * array = new array_ast(name,num,size);
				array->codegen();
			}
		}
		
	}
	// normal variable
	else
	{
		//define
		if (codestream[index] == "=")
		{
			index++;
			int number = binary_lsy();
			symbol_insert_intvalue(name, number);
			number_ast *value = new number_ast(number);
			defvariable_ast *variable = new defvariable_ast(name, value);
			variable->codegen();
		}
		//statement
		else
		{
			symbol_insert_intvalue(name, 0);
			number_ast *value = new number_ast(0);
			defvariable_ast *variable = new defvariable_ast(name, value);
			variable->codegen();
		}
	}
}
//binary expression
void parse::parse_binary(string variable_name)
{
	int number = binary_lsy();
	number_ast *value = new number_ast(number);
	defvariable_ast * variable = new defvariable_ast(variable_name, value);
	variable->codegen();
}
//function
void parse::parse_func()
{
	string func_name = codestream[index];
	function_ast * function = new function_ast(func_name);
	function->codegen();
	index = index + 4;
	if (codestream[index] == "{")
	{
		index++;
		parse_expreesion();
	}
}

void parse::parse_expreesion()
{
	while (codestream[index] != "}")
	{
		if (codestream[index] == "if")
		{
			index++;
			parse_if();
		}
		else if (codestream[index] == "while")
		{
			index++;
			parse_while();
		}
		else if (judge_variable(codestream[index]))
		{
			string variable_name = codestream[index];
			while (codestream[index] != "=")
				index++;
			index++;
			parse_binary(variable_name);
		}
		//statement or define variable
		else if (codestream[index] == "var")
		{
			index++;
			parse_defvar();
		}
		else if (codestream[index] == "\n")
			index++;
	}
}

void parse::parse_judge(exp_type type)
{
	if (codestream[index]=="(")
	{
		index++;
		vector<string> codes;
		while (codestream[index] != ")")
		{
			codes.push_back(codestream[index]);
			index++;
		}
		if (type == if_exp)
		{
			parse_bool(codes,"next");
		}
		else if (type == while_exp)
		{
			parse_bool(codes,"next");
		}
	}
	index++; //")"
}
//parse bool expression
void parse::parse_bool(vector<string> codes,string choice)
{
	string left = codes[0];
	int left_number = getvalue(left);
	immediate_ast *left_ast = new immediate_ast(left_number);
	string op = codes[1];
	string right = codes[0];
	int right_number = getvalue(right);
	immediate_ast *right_ast = new immediate_ast(right_number);
	judge_ast *judge = new judge_ast(op, left_ast, right_ast,choice);
	judge->codegen();
}

void parse::parse_if()
{
	parse_judge(if_exp);
	while (codestream[index] != "{")
		index++;
	index++;
	/*
		write label address
	*/
	sign_ast * addr_sign = new sign_ast("now");
	addr_sign->get_sign();
	addr_sign->codegen();
	/*
		block expreesion
	*/
	parse_expreesion();
	/*
		end label 
	*/
	end_ast * end = new end_ast("end");
	end->codegen();
}

void parse::parse_while()
{
	vector<string> codes;
	if (codestream[index] == "(")
	{
		int while_index = index+1;
		while (codestream[while_index] != ")")
		{
			codes.push_back(codestream[while_index]);
			while_index++;
		}
	}
	parse_judge(while_exp);
	while (codestream[index] != "{")
		index++;
	index++;
	/*
		write label address
	*/
	sign_ast * addr_sign = new sign_ast("now");
	addr_sign->get_sign();
	addr_sign->codegen();
	/*
		block expreesion
	*/
	parse_expreesion();
	/*
		end label
	*/
	end_ast * end = new end_ast("end");
	end->codegen();
	parse_bool(codes, "now");
}
