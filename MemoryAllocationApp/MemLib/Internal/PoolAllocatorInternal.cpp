#include "PoolAllocatorInternal.h"

PoolAllocatorInternal::PoolAllocatorInternal(PoolParkInternal * p_poolPark):
    m_poolPark(p_poolPark)
{

}

PoolAllocatorInternal::PoolAllocatorInternal()
{

}

PoolAllocatorInternal::~PoolAllocatorInternal()
{
}

int PoolAllocatorInternal::TestMethod()
{
    return 42;
}
