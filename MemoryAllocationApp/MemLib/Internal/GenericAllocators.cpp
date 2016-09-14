#include "GenericAllocators.h"
#include <iostream>

GenericAllocators* GenericAllocators::m_singleton = nullptr;

GenericAllocators * GenericAllocators::Get()
{
    if (m_singleton == nullptr)
    {
        m_singleton = (GenericAllocators*)malloc(sizeof(GenericAllocators));
        new (m_singleton) GenericAllocators();
    }
    return m_singleton;
}

GenericAllocators::GenericAllocators()
{
    m_default4BytePool = PoolAllocatorInternal(1);
    m_default8BytePool = PoolAllocatorInternal(1);
    m_default16BytePool = PoolAllocatorInternal(1);
}

GenericAllocators::~GenericAllocators()
{

}

PoolAllocatorInternal * GenericAllocators::GetDefault4BytePool()
{
    return &m_default4BytePool;
}

PoolAllocatorInternal * GenericAllocators::GetDefault8BytePool()
{
    return &m_default8BytePool;
}

PoolAllocatorInternal * GenericAllocators::GetDefault16BytePool()
{
    return &m_default16BytePool;
}

PoolAllocatorInternal * GenericAllocators::CreatePoolAllocator()
{
    PoolAllocatorInternal* internalPool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
    new (internalPool) PoolAllocatorInternal(2);

    return internalPool;
}
