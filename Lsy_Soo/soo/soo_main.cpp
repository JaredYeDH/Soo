//
//  main.cpp
//  Soo
//
//  Created by leviathan on 15/9/8.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include "soo_token.h"
#include "soo_parse.h"
using namespace std;

int main() {
    token tokenmachine;
    tokenmachine.tokeninit();
    tokenmachine.readline();
    parse parsemachine;
    parsemachine.build_ast(); 
    cout<<"Soo Complier is over ..."<<endl;
    return 0;
}
