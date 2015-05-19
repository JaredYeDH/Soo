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
/*
	�½��洢COFF���ű�Ľ�

	symtablename:COFF���ű���
	strtabname:����ű���ص��ַ�����
	ÿ�����Ž�Ҫ������Ӧ���ַ����ڣ��ַ����ڸ��𱣴��������
*/
Section *  COFF_FileSystem::New_CoffSymSection(char * symtablename, int charaacteristics, char * strtabname)
{
	Section *section;
	section = Section_New(symtablename, charaacteristics);
	section->link = Section_New(strtabname, charaacteristics);
	return section;
}
/*
	COFF��ʼ��
*/
void COFF_FileSystem::CoffInit()
{
	this->Nesc_Image = 0;
	Section_text = Section_New(".text", IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE);//�����
	Section_data = Section_New(".data", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA);//���ݽ�
	Section_rdata = Section_New(".rdata", IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA);
	Section_idata = Section_New(".idata", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_INITIALIZED_DATA);
	Section_bss = Section_New(".bss", IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_UNINITIALIZED_DATA);
	Section_rel = Section_New(".rel", IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_MEM_READ);
	Section_symtable = New_CoffSymSection(".symtab", IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_MEM_READ, ".strtabl");
	/*
		����COFF����
	*/
}
//���Ŀ���ļ�
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
//�ӵ�ǰ��дλ�õ�new_posλ����0��ļ�����
void Fpad(FILE * file, int new_pos)
{
	int currentpos = ftell(file);
	while (++currentpos <= new_pos)
		fputc(0, file);
}
/*
	����洢�ռ�

	type����������
	storagetype:�����洢����
	has_init:�Ƿ���г�ʼ��
	number:�������ű��
	address:�����洢��ַ
	����ֵ�������洢ֵ
*/
Section *Allocate_Storage(Data_Type *type, int storagetype, int has_init, int number, int *address)
{
	int size, align;
	Section* section = NULL;
}