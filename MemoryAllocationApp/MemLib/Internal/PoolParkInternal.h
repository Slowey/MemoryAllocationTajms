#pragma once
#include <queue>

class PoolParkInternal
{
public:
    PoolParkInternal();
    /** 
    @param1 - size in bytes of one memory block
    @param2 - number of memory blocks to create

    param1 * param2 = total allocated size in bytes
    */
    PoolParkInternal(const int& p_memoryBlockSize, const int& p_numberOfMemoryBlocks);
    ~PoolParkInternal();

    /**
    Return - a void pointer to where the blocks memory starts
    */
    void* GetNewMemoryBlockStartPoint();

private:
    std::queue<int> m_freeBlocks;
    int m_currentBlock;
    void* m_startOfMemory;
    int m_memoryBlockSize;
    // Used to ensure we dont go outside the 
    int m_numberOfMemoryBlocks;
};