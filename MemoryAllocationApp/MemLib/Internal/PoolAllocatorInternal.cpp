#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize):
    m_poolPark(p_poolPark)
{
    void* startOfPool = m_poolPark->GetNewMemoryBlockStartPoint();
    int size = m_poolPark->GetMemoryBlockSize();
    m_pools.push_back(PoolInternal(startOfPool, p_segmentSize, size));
    MemLib::OwnVector<int> testing;
    testing.push_back(1);
    testing.at(0)++;
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
    for (; i < size; i++)
    {
        if (!m_pools.at(i).Full())
        {
            break;
        }
    }
    void* memoryStartPos = m_pools.at(i).Allocate();
    numAllocations++;
    return memoryStartPos;
}

void PoolAllocatorInternal::Deallocate()
{
}
