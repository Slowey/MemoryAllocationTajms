#pragma once
#include "LibDefines.h"
#include <StackAllocator.h>
#ifndef OURLIB

class PoolAllocator
{
public:
	PoolAllocator() {}
	~PoolAllocator() {}
};
class MemoryManager
{
public:

	PoolAllocator* CreatePoolAllocator(int p_alignment);

	static MemoryManager* Get();



private:
	MemoryManager();
	~MemoryManager();
	static MemoryManager* m_singleton;

};
void* operator new[](size_t size, PoolAllocator* allocator);
void* operator new (size_t size, PoolAllocator* allocator);
void* operator new[](size_t size, Stack stackDuration);
void* operator new (size_t size, Stack stackDuration);
void operator delete (void* memBlock, size_t size, PoolAllocator* allocator);




#endif // 
