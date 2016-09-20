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
	m_currentStackBlock = p_numberOfMemoryBlocks;
}

PoolParkInternal::~PoolParkInternal()
{
}
int PoolParkInternal::GetMemoryBlockSize()
{
	return m_memoryBlockSize;
}
int PoolParkInternal::GetCurrentStackBlock()
{
	return m_currentStackBlock;
}
void* PoolParkInternal::GetNewMemoryBlockEndPoint()
{
	void* returnAddress;

	// If return block number is smaller than allocated blocks its OK

	assert(m_currentStackBlock-1 > m_currentBlock);

	//Grab last memory bit in the poolpark. Move the pointer back using currentstackblock - total memoryblocks. Multiply the sum by memoryblocksize
	returnAddress = reinterpret_cast<char*>(GetEndPointer()) + (m_currentStackBlock - m_numberOfMemoryBlocks) * m_memoryBlockSize;

	m_currentStackBlock--;
	// Return the address
	return returnAddress;
}
void * PoolParkInternal::GetNewMemoryBlockStartPoint()
{
    void* returnAddress;
    
    // Check if we have any free block in queue. If true, use that block and remove it from list
    if (!m_freedBlocks.empty())
    {
         returnAddress = m_freedBlocks.pop();
    }

    // Otherwise use the next block
    else
    {
        // If return block number is smaller than allocated blocks its OK
        assert(m_currentBlock < m_numberOfMemoryBlocks);

        // Add the block number * size of each block to the start of memory pointer
        returnAddress = reinterpret_cast<char*>(m_startOfMemory) + m_currentBlock * m_memoryBlockSize;

        m_currentBlock++;
    }

    // Return the address
    return returnAddress;
}

void PoolParkInternal::FreeMemoryBlock(void * p_blockStartPointer)
{
    m_freedBlocks.push_back(p_blockStartPointer);
}

void * PoolParkInternal::GetEndPointer()
{
	// Return the very end of the memory space of this pool
	//-1 since otherwise we'd get where the next block starts
	return reinterpret_cast<char*>(m_startOfMemory) + m_memoryBlockSize * m_numberOfMemoryBlocks - 1;
}
