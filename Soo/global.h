//
//  global.h
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#ifndef __Soo__global__
#define __Soo__global__

#include <iostream>
#include <string>
#include <vector>
using namespace std;

extern string node;
extern int nodenum;

enum var_type
{
    int_variable,
	int_array
};

enum exp_type
{
	if_exp,
	while_exp,
};
class symbol
{
public:
	string symbolname;
	int int_value;
	vector<int> array_value;
	bool isarray;
	var_type type;
};


extern vector<string> codestream;
extern vector<symbol> symboltable;

void symbol_insert_intvalue(string name,int vlaue);
void symbol_insert_intarray(string name, vector<int> &values);
bool symbol_search(string name);
int symbol_getvalue(string name);
void error(string error);

#endif /* defined(__Soo__global__) */
