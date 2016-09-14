#pragma once
#include "PoolAllocatorInternal.h"

class GenericAllocators
{
public:
    static GenericAllocators* Get();

    PoolAllocatorInternal* GetDefault4BytePool();
    PoolAllocatorInternal* GetDefault8BytePool();
    PoolAllocatorInternal* GetDefault16BytePool();

    PoolAllocatorInternal * CreatePoolAllocator();

private:
    static GenericAllocators* m_singleton;

    GenericAllocators();
    ~GenericAllocators();

    PoolAllocatorInternal m_default4BytePool;
    PoolAllocatorInternal m_default8BytePool;
    PoolAllocatorInternal m_default16BytePool;
};