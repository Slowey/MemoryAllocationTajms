#pragma once
#include "PoolAllocator.h"

class MemoryManager
{
public:

    PoolAllocator* CreatePoolAllocator();

    static MemoryManager* Get();


    PoolAllocator* GetDefault4BytePool();
    PoolAllocator* GetDefault8BytePool();
    PoolAllocator* GetDefault16BytePool();

private:
    MemoryManager();
    ~MemoryManager();
    static MemoryManager* m_singleton;
    PoolAllocator* m_default4BytePool;
    PoolAllocatorInternal m_default8BytePool;
    PoolAllocatorInternal m_default16BytePool;
};

void* operator new (size_t size, PoolAllocator* allocator);
void* operator new (size_t size);