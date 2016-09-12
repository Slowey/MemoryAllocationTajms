#pragma once
#include "../PoolAllocator.h"

class PoolAllocatorInternal
    :public PoolAllocator
{
public:
    PoolAllocatorInternal();
    ~PoolAllocatorInternal();

    int TestMethod() override;
};
