#include "AllocatorManager.h"
#include <iostream>

AllocatorManager* AllocatorManager::m_singleton = nullptr;

AllocatorManager * AllocatorManager::Get()
{
    if (m_singleton == nullptr)
    {
        m_singleton = (AllocatorManager*)malloc(sizeof(AllocatorManager));
        new (m_singleton) AllocatorManager();
    }
    return m_singleton;
}

AllocatorManager::AllocatorManager()
{
}

AllocatorManager::~AllocatorManager()
{

}

PoolAllocatorInternal * AllocatorManager::GetDefault4BytePool()
{
    return &m_default4BytePool;
}

PoolAllocatorInternal * AllocatorManager::GetDefault8BytePool()
{
    return &m_default8BytePool;
}

PoolAllocatorInternal * AllocatorManager::GetDefault16BytePool()
{
    return &m_default16BytePool;
}

PoolAllocatorInternal * AllocatorManager::CreatePoolAllocator()
{
    PoolAllocatorInternal* internalPool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
    new (internalPool) PoolAllocatorInternal();

    return internalPool;
}
