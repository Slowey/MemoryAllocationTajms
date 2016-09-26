#pragma once
#include "PoolParkInternal.h"
#include "PoolAllocatorInternal.h"


/**
Class responsible for creating all allocators, and also for
storing default pool allocators used for the general implementation
where we only overload new without calling it with specific allocators.
*/
class AllocatorManager
{
public:
    // Singleton-get
    static AllocatorManager* Get();
    /**
    Initializes pool park (which allocates all memory for the program)
    and default allocators.*/
    static void Startup(const int & p_blockSize, const int & p_numBlocks);


    // Get methods for default pools allocated to specific byte segments
    PoolAllocator* GetDefault4BytePool();
    PoolAllocator* GetDefault8BytePool();
    PoolAllocator* GetDefault16BytePool();

    // Creates a pool allocator segmented to the parameter specified
    PoolAllocator* CreatePoolAllocator(const int& p_segmentSize);

	int GetTestThingy();

	void ResetTestThingy();

private:
    static AllocatorManager* m_singleton;

    AllocatorManager(const int & p_blockSize, const int & p_numBlocks);
    ~AllocatorManager();

    PoolAllocatorInternal m_default4BytePool;
    PoolAllocatorInternal m_default8BytePool;
    PoolAllocatorInternal m_default16BytePool;

    // Pool park from which all chunks of memory are fetched
    PoolParkInternal m_poolPark;
};