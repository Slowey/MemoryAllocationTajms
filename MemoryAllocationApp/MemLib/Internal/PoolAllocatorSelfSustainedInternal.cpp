#include "PoolAllocatorSelfSustainedInternal.h"



PoolAllocatorSelfSustainedInternal::PoolAllocatorSelfSustainedInternal(PoolParkInternal * p_poolPark, const int & p_segmentSize)
    : m_poolPark(p_poolPark),m_currentPool(0), m_segmentSize(p_segmentSize), m_currentSegment(0)
{
    CreateNewPool();
    int memoryBlockSize = m_poolPark->GetMemoryBlockSize();
    m_segmentsInMemoryBlock = memoryBlockSize / p_segmentSize;
}

PoolAllocatorSelfSustainedInternal::PoolAllocatorSelfSustainedInternal()
{
}


PoolAllocatorSelfSustainedInternal::~PoolAllocatorSelfSustainedInternal()
{
}

int PoolAllocatorSelfSustainedInternal::TestMethod()
{
    return 0;
}

void* PoolAllocatorSelfSustainedInternal::Allocate()
{
    void* r_pointer;
    // Go through the pools and find one with free space
    if (!m_freedSegments.empty())
    {
        r_pointer = m_freedSegments.pop();
    }
    else
    {
        if (m_currentSegment >= m_segmentsInMemoryBlock)
        {
            CreateNewPool();
            m_currentSegment = 0;
            m_currentPool++;
        }
        r_pointer = reinterpret_cast<char*>(m_startOfMemoryBlocks.at(m_currentPool)) + m_currentSegment*m_segmentSize;
        m_currentSegment++;
    }

    return r_pointer;
}

void PoolAllocatorSelfSustainedInternal::Deallocate(void* p_memory, const int& p_size)
{
    // Need to se if the object stretches over more than one segment
    m_freedSegments.push_back(p_memory);
}

void PoolAllocatorSelfSustainedInternal::CreateNewPool()
{
    void* startOfPool = m_poolPark->GetNewMemoryBlockStartPoint();
    m_startOfMemoryBlocks.push_back(startOfPool);
}

