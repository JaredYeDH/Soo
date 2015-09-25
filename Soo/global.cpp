//
//  global.cpp
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include "global.h"
#include <string>
#include <vector>
#include <string>
using namespace std;

string node = "soo";
int nodenum = -1;
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

void symbol_insert_intvalue(string name, int value)
{
	symbol newsymbol;
	newsymbol.symbolname = name;
	newsymbol.int_value = value;
	newsymbol.isarray = false;
	symboltable.push_back(newsymbol);

}

void symbol_insert_intarray(string name, vector<int> &values)
{
	symbol newsymbol;
	newsymbol.symbolname = name;
	newsymbol.array_value = values;
	newsymbol.isarray = true;
	symboltable.push_back(newsymbol);
}

int symbol_getvalue(string name)
{
	for (int index = 0; index < symboltable.size(); index++)
	{
		if (name == symboltable[index].symbolname)
			return symboltable[index].int_value;
	}
}

void error(string strerror)
{
	cout << "Error:"<<strerror << endl;
}
