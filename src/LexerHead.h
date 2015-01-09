#ifndef _LEXERHEAD_H_
#define _LEXERHEAD_H_
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stack>
#include <boost/regex.hpp>
using namespace std;
boost::smatch what;
boost::cmatch mat;
boost::regex expression("\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")|[A-Z_a-z][A-Z_a-z0-9]*|==|!=|<=|>=|&&|\\|\\||\\p{Punct})?");
//Token��
class Token
{
public:
	bool ID;
	bool NUM;
	int linenumber;
	string text;
	Token()//�޲ι��캯��
	{
		linenumber = 0;
	}
	Token(int line)
	{
		linenumber = line;
	}
	Token(int line, string id, string ID_or_NUM)//ʹ�õĹ��캯��
	{
		linenumber = line;
		text = id;
		if (ID_or_NUM == "ID")
		{
			ID = true;
			NUM = false;
		}
		else
		{
			NUM = true;
			ID = false;
		}
	}
	int getlinenumber(){ return linenumber; }//��ô������ڵ�����
	// bool isIdenfifier(){ return false; }
	bool isnumber(){ return NUM; }
	bool isstring(){ return ID; }
	string gettext(){ return text; }
	int getnumber()//���TokenΪ���֣��������ֵ
	{
		int n = atoi(text.c_str());
		return n;
	}
};
Token StopEOF(-1);

queue<Token> Queue;
//�ʷ�����
class Lexer
{
public:
	bool hasmore;
	Lexer() //���캯��
	{
		hasmore = true;
	}
	Token  read() //��ȡ���е�һ��
	{
		if (!Queue.empty())
		{
			Token front;
			front = Queue.front();
			Queue.pop();
			return front;
		}
		else
			return StopEOF;
	}
	Token peek(int n) //Ԥ��
	{
		queue<Token > Queue_peek;
		for (int i = 0; i < n; i++)
		{
			Queue_peek.push(Queue.front());
			Queue.pop();
		}
		Token peek_token = Queue.front();
		int size = Queue.size();
		for (int i = 0; i <size; i++)
		{
			Queue_peek.push(Queue.front());
			Queue.pop();
		}
		size = Queue_peek.size();
		for (int i = 0; i <size; i++)
		{
			Queue.push(Queue_peek.front());
			Queue_peek.pop();
		}
		return peek_token;
	}
	void readline(string line, int linenumber)
	{
		int pos = 0;
		int endpos = line.length();
		string::const_iterator start = line.begin();
		string::const_iterator end = line.end();
		while (regex_search(start, end, what, expression) && pos < endpos)
		{
			string m = what[0];
			if (m.length() != 0)  //���ǿո�
			{
				if (what[2].matched == false) //����ע��
				{
					if (what[3].matched != false) //����
					{
						string msg(what[3].first, what[3].second);
						start = what[3].second;
						pos = pos + msg.length();
						Token num(linenumber, msg, "NUM");
						Queue.push(num);

					}
					else if (what[4].matched != false) //str Token ���� ����ʶ����
					{
						string msg(what[4].first, what[4].second);
						cout << msg.c_str() << endl;
						start = what[4].second;
						pos = pos + msg.length();
					}
					else //ID Token
					{
						string msg(what[0].first, what[0].second);
						start = what[0].second;
						pos = pos + msg.length();
						start = what[0].second;
						Token id(linenumber, msg, "ID");
						Queue.push(id);
					}
				}
			}
		}
		Token newline(linenumber, "\\n", "ID");
		Queue.push(newline);
	}
};
Lexer Lexer_out;//�ʷ������Ľ��
#endif