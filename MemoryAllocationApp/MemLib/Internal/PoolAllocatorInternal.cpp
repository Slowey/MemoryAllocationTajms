#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal& p_poolPark, const int& p_segmentSize):
    m_poolPark(p_poolPark)
{
    void* startOfPool = m_poolPark.GetNewMemoryBlockStartPoint();
    PoolInternal* newPool = (PoolInternal*) malloc(sizeof(PoolInternal));
    new (newPool) PoolInternal(startOfPool, p_segmentSize, m_poolPark.GetMemoryBlockSize());
}

PoolAllocatorInternal::~PoolAllocatorInternal()
{
}

int PoolAllocatorInternal::TestMethod()
{
    return 42;
}

void PoolAllocatorInternal::Allocate()
{
    numAllocations++;
}

void PoolAllocatorInternal::Deallocate()
{
}
