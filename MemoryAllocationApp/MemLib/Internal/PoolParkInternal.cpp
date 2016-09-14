#include "PoolParkInternal.h"
#include <assert.h>
#include <malloc.h>

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

    // Otherwise use the next block

    // If return block number is smaller than allocated blocks its OK
    assert(m_currentBlock < m_numberOfMemoryBlocks);
    
    // Add the block number * size of each block to the start of memory pointer
    returnAddress = reinterpret_cast<char*>(m_startOfMemory) + m_currentBlock * m_memoryBlockSize;

    m_currentBlock++;


    // Return the address
    return returnAddress;
}

void PoolParkInternal::FreeMemoryBlock(void * p_blockStartPointer)
{
    // TODO do we need to make sure the void* given is in the start of a memory block?
}
