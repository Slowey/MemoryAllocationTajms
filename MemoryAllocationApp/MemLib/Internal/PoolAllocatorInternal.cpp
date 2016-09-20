#include "PoolAllocatorInternal.h"
#include "Defines.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize):
    m_poolPark(p_poolPark), m_segmentSize(p_segmentSize)
{
    CreateNewPool();
}

PoolAllocatorInternal::PoolAllocatorInternal()
{
}

PoolAllocatorInternal::~PoolAllocatorInternal()
{
}

int PoolAllocatorInternal::TestMethod()
{
    return 42;
}

void* PoolAllocatorInternal::Allocate()
{
    // Go through the pools and find one with free space
    int size = m_pools.getSize();
    int i = 0;
    bool freePoolAvailable = false;
    for (; i < size; i++)
    {
        if (!m_pools.at(i).Full())
        {
            freePoolAvailable = true;
            break;
        }
    }
    // No free pools left, create new!
    if (!freePoolAvailable)
    {
        CreateNewPool();
        i = m_pools.getSize() - 1;
    }
    void* memoryStartPos = m_pools.at(i).Allocate();
    return memoryStartPos;
}

void PoolAllocatorInternal::Deallocate(void* p_memory, const int& p_size)
{
    // Go through the pools and find which one has the object
#ifdef SAVE_FREE_SEGMENTS_IN_POOL
    int size = m_pools.getSize();
    int i = 0;
    bool foundPool = false;
    for (; i < size; i++)
    {
        if (m_pools.at(i).FreeMemory(p_memory, p_size))
        {
            foundPool = true;
            break;
        }
    }
    if (!foundPool)
    {
        // ERROR memory isnt in given allocator
    }
#endif // SAVE_FREE_SEGMENTS_IN_POOL
}

void PoolAllocatorInternal::CreateNewPool()
{
    void* startOfPool = m_poolPark->GetNewMemoryBlockStartPoint();
    int size = m_poolPark->GetMemoryBlockSize();
    m_pools.push_back(PoolInternal(startOfPool, m_segmentSize, size));
}
