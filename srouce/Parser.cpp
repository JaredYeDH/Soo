#include "Parser.h"
#include "AST.h"
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Instance().Lexer_Read() != StopEOF)
	{
		token = Lexer::Instance().Lexer_Read();
		if (token.Token_GetText == "dec") //�����������
			Parser_Dec();
		if (token.Token_GetText == "if")  //if else ����
			Parser_If();

	}
}
//�����������
void Parser::Parser_Dec()
{
	if (Lexer::)
}