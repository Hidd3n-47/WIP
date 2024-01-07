/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#pragma once
#include "src/pch.h"

struct
{
	uint32 _allocated = 0;
	uint32 _freed = 0;
} MEM_ALLOCATION;

//// 'new' Keyword override.
//void* operator new(size_t size)
//{
//	MEM_ALLOCATION._allocated += (uint32)size;
//	return malloc(size);
//}
//
//// 'delete' Keyword override.
//void operator delete(void* memory, size_t size)
//{
//	MEM_ALLOCATION._freed += (uint32)size;
//	free(memory);
//}

void PrintMemory()
{
	std::cout << "|===================================================================|\n";
	std::cout << "|                          MEM_ALLOCATION                           |\n";
	std::cout << "|-------------------------------------------------------------------|\n";
	std::cout << "| Allocated: " << MEM_ALLOCATION._allocated << " bytes\n";
	std::cout << "| Freed: " << MEM_ALLOCATION._freed << " bytes\n";
	std::cout << "|           Leaked: " << MEM_ALLOCATION._allocated - MEM_ALLOCATION._freed << " bytes\n";
	std::cout << "|===================================================================|\n";
}