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