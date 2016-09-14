#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal()
{
}

PoolAllocatorInternal::PoolAllocatorInternal(int a)
{
    int b = 4;
}

PoolAllocatorInternal::~PoolAllocatorInternal()
{
}

int PoolAllocatorInternal::TestMethod()
{
    return 42;
}

void PoolAllocatorInternal::Allocate()
{
    numAllocations++;
}

void PoolAllocatorInternal::Deallocate()
{
}
