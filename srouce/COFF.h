#pragma once
#ifndef _COFF_H
#define _COFF_H
#include <Windows.h>
#include <string>
#include <vector>
#include "SymbolTable.h"
using namespace std;
/*
		COOF��һ�ֺ����еĶ����ļ���ʽ
		����COFF�ļ��д�������ݵĻ�����Ԫ������һ��Ŀ���ļ������д�����Ա���ϳɵ����ڣ�����ÿ��������ռһ���ڡ�
*/
//COFF�ļ�ͷ
struct Image_FileHead
{
	WORD Machine; //��ʶĿ��������͵�����
	WORD NumberOfSections;//�ڵ���Ŀ
	DWORD TimeDateStamp;//ʱ�����ָ���ļ���ʱ������
	DWORD PointerToSymbolTable;//���ű���ļ�ƫ�ƣ����������COFF���ű���ֵΪ0
	DWORD NumberOfSymbols;//���ű��е�Ԫ����Ŀ
	WORD SizeOfOptionalHeader;//��ѡ�ļ�ͷ�Ĵ�С
	WORD Characteristics;//ָʾ�ļ����Եı�־
};
//��ͷ������������ѡ�ļ�ͷ(������ڣ�
#define Image_sizeof_short_name  8;
#define CST_FUNC 0x20;					//����
#define CST_NOTFUNC 0 ;					//�Ǻ���
struct Image_SectionHead
{
	string Name;
	union
	{
		DWORD PhysicalAddress;
		DWORD VirtuallSize;
	}Misc;
	DWORD VirtualAddress;
	DWORD SizeOfRawData;
	DWORD PointerToRawData;
	DWORD PointerToRelocations;
	DWORD PonterToLinenumbers;
	WORD NumberOfRelocations;
	DWORD NumberOfLinenumbers;
	DWORD Characteristics;
};
//COFF���ű�
struct CoffSym
{
	DWORD Name;
	DWORD Next;
	DWORD Value;
	short SectionNumber;
	WORD Type;//һ����ʾ���͵�����
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
};
//COFF�ض�λ��¼��ʽ
struct CoffReloc
{
	DWORD offset;	//��Ҫ�����ض�λ�Ĵ�������ݵĵ�ַ
	DWORD cfsym;	//���ű������
	BYTE section;
	BYTE type;
};
//COFFĿ���ļ� �ڽṹ����
struct Section
{
	int data_offset;//��ǰ����ƫ��λ��
	char *data;     //������
	int data_allocated;//�����ڴ�ռ�
	char index;//�����
	struct Section * link;//�����������ڣ����Žڹ����ַ�����
	int *hashtab;//��ϣ��ֻ���ڴ洢���ű�
	Image_SectionHead sectionhead;//��ͷ
};
class COFF_FileSystem
{
public:
	static COFF_FileSystem & COFF_FileSystemInstance();
	/*
		���ݳ�Ա
	*/
	vector<Section> Sections;//�ڵĶ�̬����
	int Nesc_Image;//ӳ���ļ�����
	Section * Section_text;//�����
	Section * Section_data;//���ݽ�
	Section * Section_rdata;//ֻ�����ݽ�
	Section * Section_bss;//δ��ʼ�����ݽ�
	Section * Section_rel;//�ض�λ��Ϣ��
	Section * Section_symtable;//���ű��
	Section * Section_idata;//������
	/*
		��Ա����
	*/
	Section *Section_New(char *name, int characteristics);//�½���
	Section *Allocate_Storage(Data_Type *type, int Register, int has_init, int number, int *address);//����洢�ռ�
	void *Section_AddSize(Section *section, int increment);//��������Ԥ���ռ�
	void Section_Realloc(Section *section, int new_size);//�����������·����ڴ棬�������ݳ�ʼ��Ϊ0
	Section * New_CoffSymSection(char * symtablename, int charaacteristics, char * strtabname);//�½��洢COFF���ű�Ľ�
	int CoffSymbol_Add(Section * symtab, char *name, int value, int section_index, short type, char storageclass);//����COFF����
	void CoffSymbol_AddUpdate(Symbol * symbol, int value, int section_index, short type, char storageclass);//���ӻ����COFF���ţ�����ֻ�����ں�����������������
	char * CoffStr_Add(Section * strtabl, char *name);//����COFF�������ַ���
	int CoffSymbol_Search(Section *symtab, char *name);//����COFF����
	void CoffReloc_Add();//�����ض�λ��Ŀ
	void CoffReloc_DirectAdd();//�����ض�λ��Ϣ
	void CoffInit();//COFF��ʼ��
	void FreeSections();//�ͷ����нڵ�����
	void Output_Obj(char *name);//���Ŀ���ļ�
	void Fpad(FILE * file, int new_pos);//�ӵ�ǰ��дλ�õ�new_posλ����0��ļ�����
};
COFF_FileSystem & COFF_FileSystem::COFF_FileSystemInstance()
{
	COFF_FileSystem  coff;
	return coff;
}
#endif