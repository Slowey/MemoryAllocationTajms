#pragma once
#include "LibDefines.h"
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

	PoolAllocator* CreatePoolAllocator();

	static MemoryManager* Get();



private:
	MemoryManager();
	~MemoryManager();
	static MemoryManager* m_singleton;

};
void* operator new[](size_t size, PoolAllocator* allocator);
void* operator new (size_t size, PoolAllocator* allocator);



#endif // 
