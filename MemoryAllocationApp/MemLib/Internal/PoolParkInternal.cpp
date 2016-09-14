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
    void* returnAddress;
    
    // Check if we have any free block in queue. If true, use that block and remove it from list
    if (!m_freeBlocks.empty())
    {
        returnAddress = m_freeBlocks.front();
        m_freeBlocks.pop();
    }

    // Otherwise use the next block
    else
    {
        // If return block number is larger than allocated blocks, throw exception
        if (m_currentBlock >= m_numberOfMemoryBlocks)
        {
            throw std::exception("No available memory blocks");
        }
        // Add the block number * size of each block to the start of memory pointer
        returnAddress = reinterpret_cast<char*>(m_startOfMemory) + m_currentBlock * m_memoryBlockSize;

        m_currentBlock++;
    }

    // Return the address
    return returnAddress;
}

void PoolParkInternal::FreeMemoryBlock(void * p_blockStartPointer)
{
    // TODO do we need to make sure the void* given is in the start of a memory block?
    m_freeBlocks.push(p_blockStartPointer);
}
