#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize):
    m_poolPark(p_poolPark)
{
    void* startOfPool = m_poolPark->GetNewMemoryBlockStartPoint();
   // PoolInternal* newPool = (PoolInternal*) malloc(sizeof(PoolInternal));
   // new (newPool) PoolInternal(startOfPool, p_segmentSize, m_poolPark->GetMemoryBlockSize());
    m_pools = (std::vector<PoolInternal>*) malloc(sizeof(std::vector<PoolInternal>) + sizeof(PoolInternal) * 4);
    new (m_pools) std::vector<PoolInternal>();
    m_pools->push_back(PoolInternal(startOfPool, p_segmentSize, m_poolPark->GetMemoryBlockSize()));
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

void PoolAllocatorInternal::Allocate()
{
    numAllocations++;
}

void PoolAllocatorInternal::Deallocate()
{
}
