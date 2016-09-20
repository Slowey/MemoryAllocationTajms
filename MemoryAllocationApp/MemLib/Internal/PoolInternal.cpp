#include "PoolInternal.h"
#include <assert.h>

PoolInternal::PoolInternal(void * p_memoryStart, int p_segmentSize, int p_poolSize)
    :m_memoryStart(p_memoryStart), m_segmentSize(p_segmentSize), m_full(false), m_lastFreeSegment(0)
{
    // Calculate how many segments fit in the pool
    m_numSegments = p_poolSize / p_segmentSize;
}

PoolInternal::~PoolInternal()
{
}

void * PoolInternal::Allocate()
{
    // This should already have been done...
    assert(!m_full);
    void* returnPointer = nullptr;
    // Check if there's a free segment
    if (!m_emptySegments.empty())
    {        
        // Calculate where pointer should point and return
        returnPointer = m_emptySegments.pop();
    }
    // Take last free slot
    else
    {
        if (m_lastFreeSegment >= m_numSegments)
            m_full = true;
        // Calculate where pointer should point and return
        returnPointer = reinterpret_cast<char*> (m_memoryStart) + m_lastFreeSegment * m_segmentSize;
        // Keep track of how many segments we've used
        m_lastFreeSegment++;
    }
    return returnPointer;
}

bool PoolInternal::Full()
{
    return m_full;
}

bool PoolInternal::HasMemory(void * p_memoryPointer, const int& p_size)
{
    // Need to take size in to account...
    void* t_memoryEnd = reinterpret_cast<char*>( m_memoryStart) + m_numSegments * m_segmentSize - 1;
    if (p_memoryPointer < t_memoryEnd && p_memoryPointer >= m_memoryStart)
    {
        return true;
    }
    return false;
}

bool PoolInternal::FreeMemory(void * p_memoryPointer, const int & p_size)
{
    bool memoryWasInPool = HasMemory(p_memoryPointer, p_size);
    if (memoryWasInPool)
    {
        // Need to see if the freed memory recides over more segments...
        m_emptySegments.push_back(p_memoryPointer);
    }
    return memoryWasInPool;
}
