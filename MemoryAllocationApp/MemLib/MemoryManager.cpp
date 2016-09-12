#include "MemoryManager.h"
#include "Internal/PoolAllocatorInternal.h"


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
        m_singleton = new MemoryManager();
    return m_singleton;
}


PoolAllocator * MemoryManager::CreatePoolAllocator()
{
    return new PoolAllocatorInternal();
}


