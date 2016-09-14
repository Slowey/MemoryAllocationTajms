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
    */
    PoolAllocatorInternal(PoolParkInternal* p_poolPark);
    PoolAllocatorInternal();
    ~PoolAllocatorInternal();

    int TestMethod() override;
    void Allocate() override;
    void Deallocate() override;

    int numAllocations = 0;

private:
    PoolParkInternal* m_poolPark;
    std::vector<PoolInternal*> m_pools;
};
