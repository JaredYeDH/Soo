//
//  global.cpp
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include "global.h"
#include <vector>
#include <string>
using namespace std;

vector<string> codestream;
vector<symbol> symboltable;

bool symbol_search(string name)
{
    for (int index = 0; index < symboltable.size(); index++)
	{
		if (name == symboltable[index].symbolname)
			return true;
	}
	return false;
}

void symbol_insert(string name, int value)
{
	symbol newsymbol;
	newsymbol.symbolname = name;
	newsymbol.value = value;
	symboltable.push_back(newsymbol);
}

int symbol_getvalue(string name)
{
	for (int index = 0; index < symboltable.size(); index++)
	{
		if (name == symboltable[index].symbolname)
			return symboltable[index].value;
	}
}

void error(string strerror)
{
	cout << "Error:"<<strerror << endl;
}
