#pragma once
#ifndef _API_H
#define _API_H
class API
{
public:
	API & Instance();	//API��ʵ����
	void API_Lexer();	//���дʷ�����
	void API_Parser();	//�����﷨����
};
inline API & Instance()
{
	API api;
	return api;
}
#endif