#pragma once
#include "PoolAllocator.h"
#include "StackAllocator.h"

#define USE_LIBRARY

class MemoryManager
{
public:

    PoolAllocator* CreatePoolAllocator(const int& p_segmentSize);

    static MemoryManager* Get();

    static void Startup(const int & p_blockSize, const int & p_numBlocks);

	void ResetTestThingy();

	int GetTestThingy();



private:

    MemoryManager(const int & p_blockSize, const int & p_numBlocks);
    ~MemoryManager();
    static MemoryManager* m_singleton;

};

#ifdef USE_LIBRARY
// Don't actually need the ones that are not overrides ( new parameters) 
void* operator new[](size_t size, PoolAllocator* allocator);
void* operator new (size_t size, PoolAllocator* allocator);
void* operator new[](size_t size, Stack stackDuration);
void* operator new (size_t size, Stack stackDuration);
void* operator new (size_t size);
void operator delete(void* memBlock, PoolAllocator* allocator, size_t size);

#endif