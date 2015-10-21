//
//  token.h
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#ifndef __Soo__token__
#define __Soo__token__

#include <iostream>
#include <string>
#include "soo_global.h"
using namespace std;

class token
{
public:
    char * string2char(string str);
    static string infile;
    static string outfile;
    bool tokeninit();
    void readline();
};
#endif /* defined(__Soo__token__) */
