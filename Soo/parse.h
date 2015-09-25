//
//  parse.h
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#ifndef __Soo__parse__
#define __Soo__parse__

#include <iostream>
#include "global.h"
#include "ast.h"
using namespace std;

class parse
{
public:
    static int index;
	bool judge_op(string token);
	bool judge_variable(string variable);
	bool lowlevel(string token,string top);
	int operation(int num1, int num2, string op);
	void build_ast();
	int binary_lsy();
	int string2int(string str);
	int getvalue(string name);
	void parse_number(int number);
	void parse_defvar();						//define variable
	void parse_binary(string variable_name);	//binary expreesion
	void parse_func();	
	void parse_expreesion();
	void parse_if();
	void parse_while();
	void parse_judge(exp_type type);
	void parse_bool(vector<string> codes,string choice);
};
#endif /* defined(__Soo__parse__) */
