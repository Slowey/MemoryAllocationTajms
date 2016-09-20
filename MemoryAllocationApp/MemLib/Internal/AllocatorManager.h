#pragma once
#include "PoolAllocatorInternal.h"
#include "PoolParkInternal.h"

class AllocatorManager
{
public:
    static AllocatorManager* Get();

    static void Startup(const int & p_blockSize, const int & p_numBlocks);



    PoolAllocatorInternal* GetDefault4BytePool();
    PoolAllocatorInternal* GetDefault8BytePool();
    PoolAllocatorInternal* GetDefault16BytePool();

    PoolAllocatorInternal * CreatePoolAllocator(const int& p_segmentSize);

private:
    static AllocatorManager* m_singleton;

    AllocatorManager(const int & p_blockSize, const int & p_numBlocks);
    ~AllocatorManager();

    PoolAllocatorInternal m_default4BytePool;
    PoolAllocatorInternal m_default8BytePool;
    PoolAllocatorInternal m_default16BytePool;
    PoolParkInternal m_poolPark;
};