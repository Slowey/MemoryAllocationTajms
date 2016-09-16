#pragma once

class PoolAllocator
{
public:
    virtual int TestMethod() = 0;
    virtual void* Allocate() = 0;
    virtual void Deallocate() = 0;
};