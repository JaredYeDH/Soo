#pragma once
#ifndef once
#define _ERROR_H
#include <string>
using namespace std;
class Error
{
public:
	string Module;	 //���������ģ��
	string Function; //��������ĺ���
	string Error_Dec;//���������
	int Line;		 //�������������
	Error();
	Error(int line,string module, string function, string error_dec);
};
#endif