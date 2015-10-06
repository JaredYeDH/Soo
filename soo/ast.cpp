//
//  ast.cpp
//  Soo
//
//  Created by leviathan on 15/9/9.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "ast.h"
#include "token.h"
using namespace std;

void immediate_ast::codegen()
{
    cout << " " << number << endl;
}

void number_ast::codegen()
{
    //ofstream fout(string2char(token::outfile));
    //fout << "OPLOAD AL " << number << endl;
    cout << "OPLOAD AL " << number << endl;
}

void string_ast::codegen()
{
    cout<<"OPLOAD DL "<<"\""<<str<<"\""<<endl;
}


void strarray_ast::codegen()
{
    cout<<"OPINITLIST "<<name<<" ";
    for (int size=0; size<values.size(); size++)
        cout<<"\""<<values[size]<<"\""<<" ";
    cout<<end<<endl;
}

void intarray_ast::codegen()
{
    cout << "OPINITLIST " << name<<" ";
    for (int size = 0; size < values.size(); size++)
        cout << values[size] << " ";
    cout << end << endl;
}

void defvariable_ast::codegen()
{
    //ofstream fout(string2char(token::outfile));
    int_value->codegen();
    //fout << "OPINIT " << variable_name << " AL" << endl;
    cout << "OPINIT " << int_name << " AL" << endl;
}

void defstrvariable_ast::codegen()
{
    str_value->codegen();
    cout<<"OPINIT "<<str_name<<" DL"<<endl;
}
void assign_ast::codegen()
{
    cout<<"OPASSIGN "<<variable_name<<" "<<value_name<<endl;
}
void binary_ast::codegen()
{
    if (op=="+")
        cout<<"OPBINADD "+save+" "+left+" "+right<<endl;
    else if(op=="-")
        cout<<"OPBINSUB "+save+" "+left+" "+right<<endl;
    else if(op=="*")
        cout<<"OPBINMUL "+save+" "+left+" "+right<<endl;
    else if(op=="/")
        cout<<"OPBINDIV "+save+" "+left+" "+right<<endl;
}
void judge_ast::codegen()
{
    if (op == "<")
        cout << "JG " << left->idname << " " << right->idname << " " << sign << endl;
    else if(op==">")
        cout<<"JNG "<<left->idname<<" "<<right->idname<<" "<<sign<<endl;
}

void callfunc_ast::codegen()
{
    //ofstream fout(string2char(token::outfile));
    //fout << "JMP " <<func_name<< endl;
    cout << "JMP " << func_name << endl;
}

void function_ast::codegen()
{
    //ofstream fout(string2char(token::outfile));
    //fout << func_name << " :" << endl;
    cout << func_name << " :" << endl;
}

void sign_ast::get_sign()
{
    this->sign = getsign(this->choice);
}

void sign_ast::codegen()
{
    cout <<this->sign<< " :" << endl;
}

void end_ast::codegen()
{
    cout << end <<" "<<sign<<endl;
}

void print_ast::codegen()
{
    
}
