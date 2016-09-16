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
	if (m_singleton == nullptr)
	{
		m_singleton = (MemoryManager*)malloc(sizeof(MemoryManager));
		new (m_singleton) MemoryManager();
	}
	return m_singleton;
}


PoolAllocator * MemoryManager::CreatePoolAllocator()
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
#endif