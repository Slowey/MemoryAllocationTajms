#include "MemoryManager.h"
#include "Internal/PoolAllocatorInternal.h"
#include <iostream>

PoolAllocator * MemoryManager::CreatePoolAllocator()
{
    return new PoolAllocatorInternal();
}

void* operator new (size_t size)
{
	void* outPointer = malloc(size);

	std::cout << "Allocating" << std::endl;
	return outPointer;
}
