#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize):
    m_poolPark(p_poolPark)
{

    // PoolInternal* newPool = (PoolInternal*) malloc(sizeof(PoolInternal));
    // new (newPool) PoolInternal(startOfPool, p_segmentSize, m_poolPark->GetMemoryBlockSize());
    int* derp = new int(4);
    m_pools = new std::vector<PoolInternal>();
    //m_pools = (std::vector<PoolInternal>*) malloc(sizeof(std::vector<PoolInternal>) + sizeof(PoolInternal) * 4);
    //new (m_pools) std::vector<PoolInternal>();
    void* startOfPool = m_poolPark->GetNewMemoryBlockStartPoint();
    int size = m_poolPark->GetMemoryBlockSize();
    m_pools->push_back(PoolInternal(startOfPool, p_segmentSize, size));
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
