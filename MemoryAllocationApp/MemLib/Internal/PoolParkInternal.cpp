#include "PoolParkInternal.h"
#include <stdexcept>

PoolParkInternal::PoolParkInternal()
{
}

PoolParkInternal::PoolParkInternal(const int & p_memoryBlockSize, const int & p_numberOfMemoryBlocks): 
    m_memoryBlockSize(p_memoryBlockSize), m_numberOfMemoryBlocks(p_numberOfMemoryBlocks), m_currentBlock(0)
{
    m_startOfMemory = malloc(p_memoryBlockSize * p_numberOfMemoryBlocks);
}

PoolParkInternal::~PoolParkInternal()
{
}

void * PoolParkInternal::GetNewMemoryBlockStartPoint()
{
    int returnBlockNumber;

    // Check if we have any free block in queue. If true, use that block and remove it from list
    if (!m_freeBlocks.empty())
    {
        returnBlockNumber = m_freeBlocks.front();
        m_freeBlocks.pop();
    }

    // Otherwise use the next block
    else
    {
        returnBlockNumber = m_currentBlock;
        // If return block number is larger than allocated blocks, throw exception
        if (returnBlockNumber >= m_numberOfMemoryBlocks)
        {
            throw std::exception("No available memory blocks");
        }
        m_currentBlock++;
    }

    // Add the block number * size of each block to the start of memory pointer
    void* returnAddress;
    returnAddress = reinterpret_cast<char*>(m_startOfMemory) + returnBlockNumber * m_memoryBlockSize;

    // Return the offseted address
    return returnAddress;
}
