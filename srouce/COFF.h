#pragma once
#ifndef _COFF_H
#define _COFF_H
#include <Windows.h>
#include <string>
#include <vector>
#include "SymbolTable.h"
using namespace std;
/*
		COOF是一种很流行的对象文件格式
		节是COFF文件中代码或数据的基本单元，例如一个目标文件中所有代码可以被组合成单个节，或者每个函数独占一个节。
*/
//COFF文件头
struct Image_FileHead
{
	WORD Machine; //标识目标机器类型的数字
	WORD NumberOfSections;//节的数目
	DWORD TimeDateStamp;//时间戳，指出文件何时被创建
	DWORD PointerToSymbolTable;//符号表的文件偏移，如果不存在COFF符号表，此值为0
	DWORD NumberOfSymbols;//符号表中的元素数目
	WORD SizeOfOptionalHeader;//可选文件头的大小
	WORD Characteristics;//指示文件属性的标志
};
//节头表，这个表紧跟可选文件头(如果存在）
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
	DWORD PointerToRawData;
	DWORD PointerToRelocations;
	DWORD PonterToLinenumbers;
	WORD NumberOfRelocations;
	DWORD NumberOfLinenumbers;
	DWORD Characteristics;
};
//COFF符号表
struct CoffSym
{
	DWORD Name;
	DWORD Next;
	DWORD Value;
	short SectionNumber;
	WORD Type;//一个表示类型的数字
	BYTE StorageClass;
	BYTE NumberOfAuxSymbols;
};
//COFF重定位记录格式
struct CoffReloc
{
	DWORD offset;	//需要进行重定位的代码或数据的地址
	DWORD cfsym;	//符号表的索引
	BYTE section;
	BYTE type;
};
//COFF目标文件 节结构定义
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
class COFF_FileSystem
{
public:
	static COFF_FileSystem & COFF_FileSystemInstance();
	/*
		数据成员
	*/
	vector<Section> Sections;//节的动态数组
	int Nesc_Image;//映像文件个数
	Section * Section_text;//代码节
	Section * Section_data;//数据节
	Section * Section_rdata;//只读数据节
	Section * Section_bss;//未初始化数据节
	Section * Section_rel;//重定位信息节
	Section * Section_symtable;//符号表节
	Section * Section_idata;//导入表节
	/*
		成员函数
	*/
	Section *Section_New(char *name, int characteristics);//新建节
	Section *Allocate_Storage(Data_Type *type, int Register, int has_init, int number, int *address);//分配存储空间
	void *Section_AddSize(Section *section, int increment);//给节数据预留空间
	void Section_Realloc(Section *section, int new_size);//给节数据重新分配内存，并将内容初始化为0
	Section * New_CoffSymSection(char * symtablename, int charaacteristics, char * strtabname);//新建存储COFF符号表的节
	int CoffSymbol_Add(Section * symtab, char *name, int value, int section_index, short type, char storageclass);//增加COFF符号
	void CoffSymbol_AddUpdate(Symbol * symbol, int value, int section_index, short type, char storageclass);//增加或更新COFF符号，更新只适用于函数先声明后定义的情况
	char * CoffStr_Add(Section * strtabl, char *name);//增加COFF符号名字符串
	int CoffSymbol_Search(Section *symtab, char *name);//查找COFF符号
	void CoffReloc_Add();//增加重定位条目
	void CoffReloc_DirectAdd();//增加重定位信息
	void CoffInit();//COFF初始化
	void FreeSections();//释放所有节的数据
	void Output_Obj(char *name);//输出目标文件
	void Fpad(FILE * file, int new_pos);//从当前读写位置到new_pos位置用0填补文件内容
};
COFF_FileSystem & COFF_FileSystem::COFF_FileSystemInstance()
{
	COFF_FileSystem  coff;
	return coff;
}
#endif