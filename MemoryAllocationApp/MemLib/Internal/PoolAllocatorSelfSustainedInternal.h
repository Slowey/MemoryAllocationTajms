#pragma once
#include "../PoolAllocator.h"
#include "PoolParkInternal.h"
#include "DynamicList.h"


/**
Internal implementation of the pool allocator.
The methods here should only be called by the
new-overloads in the MemoryManager.*/
class PoolAllocatorSelfSustainedInternal
    :public PoolAllocator
{
public:
    /**
    @desc - creates one initial pool whit the size of a memory block
    @param1 - the pool park, this class will not be responsible for deleting
    */
    PoolAllocatorSelfSustainedInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize);
    PoolAllocatorSelfSustainedInternal();
    ~PoolAllocatorSelfSustainedInternal();

    int TestMethod() override;
    /** 
    Allocates a new segment and returns a pointer to it.
    It picks the first available segment from any of its pools.
    If all segments are taken, a new memory block is fetched from
    the pool park.*/
    void* Allocate() override;
    // Adds the address of the freed segment to a list to be reused
    void Deallocate(void* p_memory, const int& p_size) override;

private:
    // Tries to get a new memory chunk from the memory pool
    void CreateNewPool();
    // Stores the start of each memory chunk in a list
    MemLib::OwnVector<void*> m_startOfMemoryBlocks;
    // Stores all freed segments within the pools of this allocator
    MemLib::OwnVector<void*> m_freedSegments;
    // Pointer to pool park, which is used to request additional memory chunks
    PoolParkInternal* m_poolPark;
    // Size of each segment within the chunks
    int m_segmentSize;
    // Internal index on which pool we're currently at
    int m_currentPool;
    // How many segments there exists per block
    int m_segmentsInMemoryBlock;
    /**
    Index of current segment within a block. Whenever this increases
    past the m_segmentsInMemoryBlock, it means that the current block
    is full, and a new one will have to be requested.*/
    int m_currentSegment;
};

