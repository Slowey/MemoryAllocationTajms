#pragma once
#include <string>
#include "DynamicList.h"


////////////////WARNING! DEPRECATED AND NO LONGER USED!//////////////////
using namespace std;
class PoolInternal 
{
public:
    /**
    Creates a pool of memory. Start of memory has to be provided by allocator.
    p_segmentSize: how many bytes each segment is.
    p_poolSize: total size (in bytes) of the pool*/
    PoolInternal(void* p_memoryStart, int p_segmentSize, int p_poolSize);
    ~PoolInternal();

    /**
    Returns pointer to a free memory slot*/
    void* Allocate();

    /**
    Returns if the pool is full*/
    bool Full();

    /**
    Checks if a pointer recides in the pool
    */
    bool HasMemory(void* p_memoryPointer, const int& p_size);

    /**
    Frees the memory if it recides in the pool
    */
    bool FreeMemory(void* p_memoryPointer, const int& p_size);

private:
    // Pointer to start of memory for this pool
    void* m_memoryStart;

    // Size of each segment within the pool
    int m_segmentSize;

    /** 
    States whether the pool is full or not. This is used
    by the pool allocator to know which pool memory should 
    be allocated in*/
    bool m_full;

    // Index of last free index in memory pool
    int m_lastFreeSegment;

    // Number of segments in this pool
    int m_numSegments;

    // Queue of pointer to start of empty segments
    MemLib::OwnVector<void*> m_emptySegments;
};