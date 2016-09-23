#pragma once
#include "../PoolAllocator.h"
#include "PoolParkInternal.h"
#include "PoolInternal.h"
#include "DynamicList.h"



//////////////WARNING! DEPRECATED CLASS! NOT USED/////////////////
/**
Internal implementation of the pool allocator.
The methods here should only be called by the
new-overloads in the MemoryManager.*/
class PoolAllocatorInternal
    :public PoolAllocator
{
public:
    /**
    @desc - creates one initial pool whit the size of a memory block
    @param1 - the pool park, this class will not be responsible for deleting
    */
    PoolAllocatorInternal(PoolParkInternal* p_poolPark, const int& p_segmentSize);
    PoolAllocatorInternal();
    ~PoolAllocatorInternal();

    int TestMethod() override;
    // Allocates a new segment and returns a pointer to it
    void* Allocate() override;
    // Adds the address of the freed segment to a list to be reused
    void Deallocate(void* p_memory, const int& p_size) override;

private:
    // Tries to get a new memory chunk from the memory pool
    void CreateNewPool();
    // Stores all pools used by the pool allocator
    MemLib::OwnVector<PoolInternal> m_pools;
    // Pointer to pool park. Used to get new memory chunk
    PoolParkInternal* m_poolPark;
    // Stores how big each segment of the chunk is
    int m_segmentSize;
};
