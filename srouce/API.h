#include "API.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void API::API_Welcome()
{
	string command;
	cout << "       Welcome to Soo       " << endl;
	cout << "            by:Leviathan1995" << endl;
	cout << "File or Input: f or i       " << endl;
	cout << "Please select:              " << endl;
	cin >> command;
	if (command == "f")
		API_ReadFile();
	else
		API_ShellInput();
}

//���ļ��ж�ȡ����
void API::API_ReadFile()
{
	int LineNumber = 0;
	Token token;
	ifstream Infile("code.txt");
	string Line;
	while (getline(Infile, Line))
	{
		LineNumber++;
		Lexer::Instance().Lexer_Readline(Line, LineNumber);
	}
	API::Instance().API_Parser();
}

//�����﷨����
void API::API_Parser()
{
	P
}