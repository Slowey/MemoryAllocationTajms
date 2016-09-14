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



PoolAllocator * MemoryManager::CreatePoolAllocator()
{
    return AllocatorManager::Get()->CreatePoolAllocator();
}

void* operator new[] (size_t size, PoolAllocator* allocator)
{
    void* outpointer = operator new (size, allocator);
    return outpointer;
}

void* operator new (size_t size, PoolAllocator* allocator)
{
    void* outPointer = malloc(size);

    std::cout << "Allocating with allocator" << std::endl;
    allocator->Allocate();

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
        std::cout << "Allocating from 4" << std::endl;
    }
    else if (size <= 8)
    {
        allocator = AllocatorManager::Get()->GetDefault8BytePool();
        std::cout << "Allocating from 8" << std::endl;
    }
    else if (size <= 16)
    {
        allocator = AllocatorManager::Get()->GetDefault16BytePool();
        std::cout << "Allocating from 16" << std::endl;
    }
    else
    {
        std::cout << "Not implemented allocating normal" << std::endl;
        outPointer = malloc(size);
    }

    // Allocate from correct pool
    if(outPointer == nullptr)
        outPointer = operator new (size, allocator);
    
	return outPointer;
}