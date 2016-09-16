#pragma once
#include "PoolAllocator.h"
#include "Internal\StackAllocatorInternal.h"
#define USE_LIBRARY

class MemoryManager
{
public:

    PoolAllocator* CreatePoolAllocator(const int& p_segmentSize);

    static MemoryManager* Get();



private:
    MemoryManager();
    ~MemoryManager();
    static MemoryManager* m_singleton;
	StackAllocatorInternal* m_stackAllocator;

};

#ifdef USE_LIBRARY
void* operator new[](size_t size, PoolAllocator* allocator);
void* operator new (size_t size, PoolAllocator* allocator);
void* operator new[](size_t size, Stack stackDuration);
void* operator new (size_t size, Stack stackDuration);
void* operator new (size_t size);
#endif