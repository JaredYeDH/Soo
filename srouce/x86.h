/*
	����x86��������
*/
#pragma once
#ifndef _X86_H
#define _X86_H
#include "Global.h"
#include "SymbolTable.h"
//�������洢�ṹ
struct Operand
{
	Data_Type type;//��������
	unsigned short Register;//�Ĵ�����洢����
	int value;//����ֵ
	struct Symbol * symbol;//��������
};
//����x86��������
class CodeGenerate
{
public:
	//����ͨ��ָ��
	void GenerateByte(char c);//������д��һ���ֽ�
	void GeneratePrefix(char opcode);//����ָ��ǰ׺
	void GenerateOpcode1(char opcode);//���ɵ��ֽ�ָ��
	void GenerateOpcode2(char first, char second);//����˫�ֽ�ָ��
	void GenerateModrm(int mod, int sourceOp, int destinationOp, Symbol *symbol, int correlationvalue);//����ָ��Ѱַ��ʽ�ֽ� ModeR/M
	void GenerateDword(unsigned int c);//����4�ֽڲ�����
	void GenerateAdd32(int Register, Symbol *symbol, int correlationvalue);//����ȫ�ַ��ŵ�ַ��������COFF�ض�λ��¼
	//�������ݴ���ָ��
	void GenerateLoad(int Register, Operand *operand);//��������operand���ص��Ĵ���Register����
	void GenerateStore(int Register, Operand *operand);//���Ĵ���Register�е�ֵ���������operand��
};
#endif