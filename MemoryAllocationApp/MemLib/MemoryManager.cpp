#include "MemoryManager.h"
#include "Internal/AllocatorManager.h"
#include <iostream>


MemoryManager* MemoryManager::m_singleton = nullptr;

MemoryManager::MemoryManager()
{
    AllocatorManager::Get(); // Initialize
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


PoolAllocator * MemoryManager::CreatePoolAllocator(const int& p_segmentSize)
{
    return AllocatorManager::Get()->CreatePoolAllocator(p_segmentSize);
}
#ifdef USE_LIBRARY

void* operator new[] (size_t size, PoolAllocator* allocator)
{
    void* outpointer = operator new (size, allocator);
    return outpointer;
}

void* operator new (size_t size, PoolAllocator* allocator)
{
    void* outPointer = allocator->Allocate();

    return outPointer;
}

void* operator new (size_t size)
{	
    PoolAllocator* allocator = nullptr;
    void* outPointer = nullptr;
    // Choose pool to allocate depending on size
    if (size <= 4)
    {
        allocator = AllocatorManager::Get()->GetDefault4BytePool();
    }
    else if (size <= 8)
    {
        allocator = AllocatorManager::Get()->GetDefault8BytePool();
    }
    else if (size <= 16)
    {
        allocator = AllocatorManager::Get()->GetDefault16BytePool();
    }
    else
    {
        outPointer = malloc(size);
    }

    // Allocate from correct pool
    if(outPointer == nullptr)
        outPointer = operator new (size, allocator);
    
	return outPointer;
}

#endif