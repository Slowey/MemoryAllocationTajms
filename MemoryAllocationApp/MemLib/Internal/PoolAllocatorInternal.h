#pragma once
#include "../PoolAllocator.h"
#include "../Internal/PoolParkInternal.h"
#include "../Internal/PoolInternal.h"

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
    void Allocate() override;
    void Deallocate() override;

    int numAllocations = 0;

private:
    PoolParkInternal* m_poolPark;
    std::vector<PoolInternal>* m_pools;
};
