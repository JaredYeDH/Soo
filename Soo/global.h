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

struct symbol
{
    string symbolname;
	int value;
};

extern vector<string> codestream;
extern vector<symbol> symboltable;

void symbol_insert(string name,int vlaue);
bool symbol_search(string name);
int symbol_getvalue(string name);
void error(string error);

#endif /* defined(__Soo__global__) */
