#pragma once
#include "../PoolAllocator.h"

class PoolAllocatorInternal
    :PoolAllocator
{
public:
    PoolAllocatorInternal();
    ~PoolAllocatorInternal();

    int TestMethod() override;
};
