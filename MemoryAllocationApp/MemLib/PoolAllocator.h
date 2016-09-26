#pragma once
/**
Store a pointer to a pool allocator to use when explicitly calling
new overload with a pool allocator. The method is called from the
memory manager.*/
class PoolAllocator
{
public:
    virtual int TestMethod() = 0;
    virtual void* Allocate() = 0;
    virtual void Deallocate(void* p_memory, const int& p_size) = 0;
};