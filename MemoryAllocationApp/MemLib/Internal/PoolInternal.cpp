#include "PoolInternal.h"
#include <assert.h>

PoolInternal::PoolInternal(void * p_memoryStart, int p_segmentSize, int p_poolSize)
    :m_memoryStart(p_memoryStart), m_segmentSize(p_segmentSize)
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
    assert(m_full);
    // Check if there's a free segment
    if (m_emptySegments.size() > 0)
    {
        // Get segment
        int segment = m_emptySegments.front();
        // Remove from queue
        m_emptySegments.pop();
        // Calculate where pointer should point and return
        return reinterpret_cast <char*> (m_memoryStart) + segment * m_segmentSize;
    }
    // Take last free slot
    else
    {
        // Keep track of how many segments we've used
        m_lastFreeSegment++;
        if (m_lastFreeSegment >= m_numSegments)
            m_full = true;
        // Calculate where pointer should point and return
        return reinterpret_cast<char*> (m_memoryStart) + m_lastFreeSegment * m_segmentSize;
    }
}

bool PoolInternal::Full()
{
    return m_full;
}
