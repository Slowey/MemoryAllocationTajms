#include "MemoryManager.h"
#include "Internal/PoolAllocatorInternal.h"
#include <iostream>


MemoryManager* MemoryManager::m_singleton = nullptr;

MemoryManager::MemoryManager()
{
    static PoolAllocatorInternal derp;
    m_default4BytePool = &derp;



   m_default4BytePool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
   PoolAllocatorInternal* internalPool = static_cast<PoolAllocatorInternal*>(m_default4BytePool);
   new PoolAllocatorInternal();
   //m_default4BytePool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
   //PoolAllocatorInternal* internalPool = static_cast<PoolAllocatorInternal*>(m_default4BytePool);
   //new (internalPool) PoolAllocatorInternal();
   //
   //m_default8BytePool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
   //internalPool = static_cast<PoolAllocatorInternal*>(m_default8BytePool);
   //new (internalPool) PoolAllocatorInternal();
   //
   //m_default16BytePool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
   //internalPool = static_cast<PoolAllocatorInternal*>(m_default16BytePool);
   //new (internalPool) PoolAllocatorInternal();
}

MemoryManager::~MemoryManager()
{
}

MemoryManager * MemoryManager::Get()
{
    if (m_singleton == nullptr)
    {
        m_singleton = (MemoryManager*)malloc(sizeof(MemoryManager));
        *m_singleton = MemoryManager();
    }
    return m_singleton;
}

PoolAllocator * MemoryManager::GetDefault4BytePool()
{
    PoolAllocator* ret = &m_default4BytePool;
    return ret;
}

PoolAllocator * MemoryManager::GetDefault8BytePool()
{
    return &m_default8BytePool;
}

PoolAllocator * MemoryManager::GetDefault16BytePool()
{
    return &m_default16BytePool;
}

PoolAllocator * MemoryManager::CreatePoolAllocator()
{
    PoolAllocatorInternal* internalPool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
    new (internalPool) PoolAllocatorInternal();

    int *a = new (internalPool)int();

    return internalPool;
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
    PoolAllocator* allocator;
    // Choose pool to allocate depending on size
    if (size <= 4)
    {
        allocator = MemoryManager::Get()->GetDefault4BytePool();
        std::cout << "Allocating from 4" << std::endl;
    }
    else if (size <= 8)
    {
        allocator = MemoryManager::Get()->GetDefault8BytePool();
        std::cout << "Allocating from 8" << std::endl;
    }
    else if (size <= 16)
    {
        allocator = MemoryManager::Get()->GetDefault16BytePool();
        std::cout << "Allocating from 16" << std::endl;
    }
    else
    {
        std::cout << "Not implemented" << std::endl;
        return nullptr;
    }

    // Allocate from correct pool
    void* outPointer = operator new (size, allocator);
    
	return outPointer;
}