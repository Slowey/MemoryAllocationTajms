#pragma once
#include "../PoolAllocator.h"

class PoolAllocatorInternal
    :public PoolAllocator
{
public:
    PoolAllocatorInternal();
    PoolAllocatorInternal(int a);
    ~PoolAllocatorInternal();

    int TestMethod() override;
    void Allocate() override;
    void Deallocate() override;

    int numAllocations = 0;
};
