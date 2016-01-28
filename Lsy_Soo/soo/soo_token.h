//
//  token.h
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#ifndef _SOO_TOKEN_H
#define _SOO_TOKEN_H

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
