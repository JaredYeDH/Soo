#pragma once
#ifndef _COFF_H
#define _COFF_H
#include <Windows.h>
#include <string>
using namespace std;
//��ͷ��
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
	DWORD PointerToRelocation;
	WORD PonterToLinenumbers;
	WORD NumberOfRelocations;
	DWORD Characteristics;
};
//COFF�ļ�ͷ
struct Image_FileHead
{
	WORD Machine; //��ʶĿ��������͵�����
	WORD NumberOfSections;//�ڵ���Ŀ
	DWORD TimeDateStamp;//ʱ�����ָ���ļ���ʱ������
	DWORD PointerToSymbolTable;//���ű���ļ�ƫ��
	DWORD NumberOfSymbols;//���ű��е�Ԫ����Ŀ
	WORD SizeOfOptionalHeader;//��ѡ�ļ�ͷ�Ĵ�С
	WORD Characteristics;//ָʾ�ļ����Եı�־
};
//COFF���ű��¼��Ա
struct CoffSym
{
	DWORD Name;
	DWORD Next;
	DWORD Value;
	short SectionNumber;
	WORD Type;
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
};
//COFF�ض�λ����Ա����
struct CoffReloc
{
	DWORD offset;	//��Ҫ�����ض�λ�Ĵ�������ݵĵ�ַ
	DWORD cfsym;	//���ű������
	BYTE section;
	BYTE type;
};
//�ڽṹ����
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
Section * Section_New(string name, int Characteristics)
{
	Section * section = new Section;
	int initsize = 8;
	section->sectionhead.Name = name;
	section->sectionhead.Characteristics = Characteristics;
	section->data = new char[initsize];
	section->data_allocated = initsize;
	if (!(Characteristics& IMAGE_SCN_LNK_REMOVE))
		nesc_image++;
	dynarry_add(&sections, section);
	return section;
}
#endif