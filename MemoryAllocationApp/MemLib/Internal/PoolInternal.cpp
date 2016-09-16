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
        // Get segment and remove from queue
        int segment = m_emptySegments.pop();
        
        // Calculate where pointer should point and return
        returnPointer = reinterpret_cast <char*> (m_memoryStart) + segment * m_segmentSize;
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
