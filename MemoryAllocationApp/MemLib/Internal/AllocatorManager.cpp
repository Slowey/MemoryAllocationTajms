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
    m_poolPark = PoolParkInternal(1024, 20);
    PoolAllocatorInternal hej;
    m_default4BytePool = PoolAllocatorInternal(&m_poolPark,4);
    m_default8BytePool = PoolAllocatorInternal(&m_poolPark, 8);
    m_default16BytePool = PoolAllocatorInternal(&m_poolPark, 16);
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
