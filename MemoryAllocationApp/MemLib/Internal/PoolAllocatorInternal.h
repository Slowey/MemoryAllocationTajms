#pragma once
#include "../PoolAllocator.h"
#include "PoolParkInternal.h"
#include "PoolInternal.h"
#include "DynamicList.h"

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
    void* Allocate() override;
    void Deallocate(void * memBlock, size_t size);

private:
    void CreateNewPool();
    MemLib::OwnVector<PoolInternal> m_pools;
    PoolParkInternal* m_poolPark;
    int m_segmentSize;
};
