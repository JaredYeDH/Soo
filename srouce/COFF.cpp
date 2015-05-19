#include "COFF.h"
#include "Error.h"
#include "Lexer.h"
using namespace std;
/*
	功能：新建节
	name: 节名称
	Characteristics: 节属性
	返回值： 新增加的节
	Nsec_Image: 映像文件中节个数
*/
Section * COFF_FileSystem::Section_New(char *name, int characteristics)
{
	Section * section;
	int Initsize = 8;
	section =(Section*)malloc(sizeof(Section));
	section->sectionhead.Name = name;
	section->sectionhead.Characteristics = characteristics;
	section->index = Sections.size() + 1;
	section->data = new char;
	section->data_allocated = Initsize;
	if (!(characteristics&IMAGE_SCN_LNK_REMOVE))
		Nesc_Image++;
	Sections.push_back(*section);
	return section;
}
/*
	给节数据预留increment大小的内存空间
	section: 预留内存空间的节
	increment:预留的空间大小
	返回值：预留内存空间的首地址
*/
void * COFF_FileSystem::Section_AddSize(Section *section, int increment)
{
	int offset, offsetfirst;
	offset = section->data_offset;
	offsetfirst = offset + increment;
	if (offsetfirst > section->data_allocated)
		Section_Realloc(section, offsetfirst);
	section->data_offset = offsetfirst;
	return section->data + offset;
}
//给节数据重新分配内存，并将内容初始化为0
void COFF_FileSystem::Section_Realloc(Section *section, int new_size)
{
	int size;
	char *data;
	size = section->data_allocated;
	while (size < new_size)
		size = size * 2;
	data =(char *)realloc(section->data, size);
	if (!data)
	{
		Error error(0, "COFF", "Section_Realloc", "memory allocation failed");
		error.ThrowError();
	}
	memset(data + section->data_allocated, 0, size - section->data_allocated);//节数据初始化为0
	section->data = data;
	section->data_allocated = size;
}
/*
	新建存储COFF符号表的节

	symtablename:COFF符号表名
	strtabname:与符号表相关的字符串表
	每个符号节要有其相应的字符串节，字符串节负责保存符号名称
*/
Section *  COFF_FileSystem::New_CoffSymSection(char * symtablename, int charaacteristics, char * strtabname)
{
	Section *section;
	section = Section_New(symtablename, charaacteristics);
	section->link = Section_New(strtabname, charaacteristics);
	return section;
}
/*
	COFF初始化
*/
void COFF_FileSystem::CoffInit()
{
	this->Nesc_Image = 0;
	Section_text = Section_New(".text", IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE);//代码节
	Section_data = Section_New(".data", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA);//数据节
	Section_rdata = Section_New(".rdata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA);
	Section_idata = Section_New(".idata", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA);
	Section_bss = Section_New(".bss", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_UNINITIALIZED_DATA);
	Section_rel = Section_New(".rel", IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_MEM_READ);
	Section_symtable = New_CoffSymSection(".symtab", IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_MEM_READ, ".strtabl");
	/*
		增加COFF符号
	*/
}
//输出目标文件
void COFF_FileSystem::Output_Obj(char *name)
{
	int FileOffset;
	FILE * Fout = fopen(name, "wb");
	int i, Sh_size, Nesc_obj = 0;
	IMAGE_FILE_HEADER * FileHead;
	Nesc_Image = Sections.size() - 2;
	Sh_size = sizeof(IMAGE_SECTION_HEADER);
	FileOffset = sizeof(IMAGE_FILE_HEADER)+Nesc_obj*Sh_size;
	Fpad(Fout, FileOffset);
	FileHead = new IMAGE_FILE_HEADER;
	for (i = 0; i < Nesc_obj; i++)
	{
		Section *section = &Sections[i];
		if (section->data == NULL)
			continue;
		fwrite(section->data, 1, section->data_offset, Fout);
		section->sectionhead.PointerToRawData = FileOffset;
		section->sectionhead.SizeOfRawData = section->data_offset;
		FileOffset += section->data_offset;
	}
	fseek(Fout, SEEK_SET, 0);
	FileHead->Machine = IMAGE_FILE_MACHINE_I386;
	FileHead->NumberOfSections = Nesc_obj;
	FileHead->PointerToSymbolTable = Section_symtable->sectionhead.PointerToRelocations;
	FileHead->NumberOfSymbols = Section_symtable->sectionhead.SizeOfRawData / sizeof(CoffSym);
	fwrite(FileHead, 1, sizeof(IMAGE_FILE_HEADER), Fout);
	for (i = 0; i < Nesc_obj; i++)
	{
		Section *section = &Sections[i];
		void *vp = static_cast<void*>(new std::string(section->sectionhead.Name));
		fwrite(vp, 1,Sh_size, Fout);
	}
	free(FileHead);
	fclose(Fout);
}
//从当前读写位置到new_pos位置用0填补文件内容
void Fpad(FILE * file, int new_pos)
{
	int currentpos = ftell(file);
	while (++currentpos <= new_pos)
		fputc(0, file);
}
/*
	分配存储空间

	type：变量类型
	storagetype:变量存储类型
	has_init:是否进行初始化
	number:变量符号编号
	address:变量存储地址
	返回值：变量存储值
*/
Section *Allocate_Storage(Data_Type *type, int storagetype, int has_init, int number, int *address)
{
	int size, align;
	Section* section = NULL;
}