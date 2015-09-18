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
	void parse_number(int number);
	void parse_defvar();						//define variable
	void parse_binary(string variable_name);	//binary expreesion
	void parse_func();	
	void parse_expreesion();
	void parse_if();
	void parse_judge();
};
#endif /* defined(__Soo__parse__) */
