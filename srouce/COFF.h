#pragma once
#ifndef _COFF_H
#define _COFF_H
#include <Windows.h>
#include <string>
using namespace std;
//节头表
#define Image_sizeof_short_name  8;
#define CST_FUNC 0x20;					//函数
#define CST_NOTFUNC 0 ;					//非函数
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
//COFF文件头
struct Image_FileHead
{
	WORD Machine; //标识目标机器类型的数字
	WORD NumberOfSections;//节的数目
	DWORD TimeDateStamp;//时间戳，指出文件何时被创建
	DWORD PointerToSymbolTable;//符号表的文件偏移
	DWORD NumberOfSymbols;//符号表中的元素数目
	WORD SizeOfOptionalHeader;//可选文件头的大小
	WORD Characteristics;//指示文件属性的标志
};
//COFF符号表记录成员
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
//COFF重定位各成员变量
struct CoffReloc
{
	DWORD offset;	//需要进行重定位的代码或数据的地址
	DWORD cfsym;	//符号表的索引
	BYTE section;
	BYTE type;
};
//节结构定义
struct Section
{
	int data_offset;//当前数据偏移位置
	char *data;     //节数据
	int data_allocated;//分配内存空间
	char index;//节序号
	struct Section * link;//关联的其他节，符号节关联字符串节
	int *hashtab;//哈希表，只用于存储符号表
	Image_SectionHead sectionhead;//节头
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