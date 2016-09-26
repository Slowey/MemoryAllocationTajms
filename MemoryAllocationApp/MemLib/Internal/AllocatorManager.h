#pragma once

#define SELF_SUSTAINED_POOL_ALLOCATOR

#include "PoolAllocatorInternal.h"
#ifdef SELF_SUSTAINED_POOL_ALLOCATOR
#include "PoolAllocatorSelfSustainedInternal.h"
#else
#include "PoolParkInternal.h"
#endif



class AllocatorManager
{
public:
    static AllocatorManager* Get();

    static void Startup(const int & p_blockSize, const int & p_numBlocks);



    PoolAllocator* GetDefault4BytePool();
    PoolAllocator* GetDefault8BytePool();
    PoolAllocator* GetDefault16BytePool();

    PoolAllocator* CreatePoolAllocator(const int& p_segmentSize);

	int GetTestThingy();

	void ResetTestThingy();

private:
    static AllocatorManager* m_singleton;

    AllocatorManager(const int & p_blockSize, const int & p_numBlocks);
    ~AllocatorManager();

    #ifdef SELF_SUSTAINED_POOL_ALLOCATOR
    PoolAllocatorSelfSustainedInternal m_default4BytePool;
    PoolAllocatorSelfSustainedInternal m_default8BytePool;
    PoolAllocatorSelfSustainedInternal m_default16BytePool;
    #else
    PoolAllocatorInternal m_default4BytePool;
    PoolAllocatorInternal m_default8BytePool;
    PoolAllocatorInternal m_default16BytePool;
    #endif


    PoolParkInternal m_poolPark;
};