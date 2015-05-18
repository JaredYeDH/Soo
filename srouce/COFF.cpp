#include "COFF.h"
#include "Error.h"
#include "Lexer.h"
using namespace std;
/*
	���ܣ��½���
	name: ������
	Characteristics: ������
	����ֵ�� �����ӵĽ�
	Nsec_Image: ӳ���ļ��нڸ���
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
	��������Ԥ��increment��С���ڴ�ռ�
	section: Ԥ���ڴ�ռ�Ľ�
	increment:Ԥ���Ŀռ��С
	����ֵ��Ԥ���ڴ�ռ���׵�ַ
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
//�����������·����ڴ棬�������ݳ�ʼ��Ϊ0
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
	memset(data + section->data_allocated, 0, size - section->data_allocated);//�����ݳ�ʼ��Ϊ0
	section->data = data;
	section->data_allocated = size;
}