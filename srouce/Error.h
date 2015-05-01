#pragma once
#ifndef once
#define _ERROR_H
#include <string>
using namespace std;
class Error
{
public:
	Error & Error_Instance();
	string Module;	 //���������ģ��
	string Function; //��������ĺ���
	string Error_Dec;//���������
	int Line;		 //�������������
	Error();
	Error(int line,string module, string function, string error_dec);//һ��Ϊ�﷨����ʱ�������Ĵ���
	Error(string module, string function, string error_dec);//�������
	string ThrowError(); //�������
};
inline Error & Error_Instance()
{
	Error error;
	return error;
}
#endif