#include "MemoryManagerDummy.h"
#ifndef OURLIB
#include <iostream>


MemoryManager* MemoryManager::m_singleton = nullptr;

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}

MemoryManager * MemoryManager::Get()
{
	return m_singleton;
}

void MemoryManager::Startup(const int & p_blockSize, const int & p_numBlocks)
{
    if (m_singleton != nullptr)
    {
        return;
    }
    m_singleton = (MemoryManager*)malloc(sizeof(MemoryManager));
    new (m_singleton) MemoryManager();
}


PoolAllocator * MemoryManager::CreatePoolAllocator(int p_alignment)
{
	return new PoolAllocator();
}
void* operator new[](size_t size, PoolAllocator* allocator)
{
	void* outpointer = operator new (size, allocator);
	return outpointer;
}

void* operator new (size_t size, PoolAllocator* allocator)
{
	void* outPointer = malloc(size);
	return outPointer;
}
void* operator new (size_t size, Stack p_stackDuration)
{
	void* outPointer = malloc(size);
	return outPointer;
}
void* operator new[](size_t size, Stack p_stackDuration)
{
	void* outPointer = malloc(size);
	return outPointer;
}
void operator delete(void* memBlock, PoolAllocator* allocator, size_t size)
{
    delete memBlock;
}

#endif