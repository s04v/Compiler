#include <mInput.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <assert.h>

char* mInput::code = 0;
//TODO: fix input bugs 
void mInput::load_code(const char* filename) {
	HANDLE file = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	assert(file != INVALID_HANDLE_VALUE);
	DWORD file_size = GetFileSize(file, 0);
	HANDLE file_mapping = CreateFileMappingA(file, 0, PAGE_WRITECOPY, 0, 0, 0);
	assert(file_mapping);
	char* file_memory = (char *)MapViewOfFileEx(file_mapping, FILE_MAP_COPY, 0, 0, 0, 0);
	assert(file_memory);
	assert(file_size > 0);
	mInput::code = file_memory;

	std::cout << "finish load code!\n";
	std::cout << mInput::code << std::endl;

}