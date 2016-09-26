#include "AllocatorManager.h"
#include "StackAllocatorInternal.h"
#include <iostream>

AllocatorManager* AllocatorManager::m_singleton = nullptr;

AllocatorManager * AllocatorManager::Get()
{
    return m_singleton;
}

void AllocatorManager::Startup(const int &p_blockSize, const int &p_numBlocks)
{
    if (m_singleton != nullptr)
    {
        return; // assert? throw?
    }

    m_singleton = (AllocatorManager*)malloc(sizeof(AllocatorManager));
    new (m_singleton) AllocatorManager(p_blockSize, p_numBlocks);

}

AllocatorManager::AllocatorManager(const int &p_blockSize, const int &p_numBlocks)
{
    m_poolPark = PoolParkInternal(p_blockSize, p_numBlocks);
	StackAllocatorInternal::Initialize(m_poolPark.GetEndPointer(), &m_poolPark);

#ifdef SELF_SUSTAINED_POOL_ALLOCATOR
    m_default4BytePool = PoolAllocatorSelfSustainedInternal(&m_poolPark, 4);
    m_default8BytePool = PoolAllocatorSelfSustainedInternal(&m_poolPark, 8);
    m_default16BytePool = PoolAllocatorSelfSustainedInternal(&m_poolPark, 16);
#else
    m_default4BytePool = PoolAllocatorInternal(&m_poolPark, 4);
    m_default8BytePool = PoolAllocatorInternal(&m_poolPark, 8);
    m_default16BytePool = PoolAllocatorInternal(&m_poolPark, 16);
#endif
}

AllocatorManager::~AllocatorManager()
{

}

PoolAllocator * AllocatorManager::GetDefault4BytePool()
{
    return &m_default4BytePool;
}

PoolAllocator * AllocatorManager::GetDefault8BytePool()
{
    return &m_default8BytePool;
}

PoolAllocator * AllocatorManager::GetDefault16BytePool()
{
    return &m_default16BytePool;
}


PoolAllocator * AllocatorManager::CreatePoolAllocator(const int& p_segmentSize)
{
    PoolAllocatorInternal* internalPool = (PoolAllocatorInternal*)malloc(sizeof(PoolAllocatorInternal));
    new (internalPool) PoolAllocatorInternal(&m_poolPark, p_segmentSize);

    return internalPool;
}

int AllocatorManager::GetTestThingy()
{
	return m_poolPark.GetTestThreadNr();
}
void AllocatorManager::ResetTestThingy()
{
	m_poolPark.ResetTestNumber();
}
