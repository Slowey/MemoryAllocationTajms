#include "StackAllocatorInternal.h"
#include <string>

StackAllocatorInternal* StackAllocatorInternal::m_singleton = nullptr;

StackAllocatorInternal::StackAllocatorInternal(void * p_start, PoolParkInternal* p_poolPark)
	:m_startPointer(p_start), m_head(p_start), m_poolPark(p_poolPark)
{
	m_currentBlock = m_poolPark->GetCurrentStackBlock();
	m_totalNrOfBlocks = m_currentBlock;
}

StackAllocatorInternal::~StackAllocatorInternal()
{
}



StackAllocatorInternal * StackAllocatorInternal::Get()
{
	if (m_singleton == nullptr)
	{
		// Not initialized.
		printf("StackallocatorInternal is not initialized!");
		return nullptr;
	}
	return m_singleton;
}

void StackAllocatorInternal::Initialize(void* p_start, PoolParkInternal* p_poolPark)
{
	m_singleton = (StackAllocatorInternal*)malloc(sizeof(StackAllocatorInternal));
	new (m_singleton) StackAllocatorInternal(p_start, p_poolPark);
}

void* StackAllocatorInternal::Allocate(size_t p_numBytes)
{
	// Check if this allocate will bust the current pool.
	int t_blockSize = m_poolPark->GetMemoryBlockSize();
	//if ((reinterpret_cast<char*>(m_head) - p_numBytes) < ((reinterpret_cast<char*>(m_poolPark->GetEndPointer()) + ((m_currentBlock-1) - m_totalNrOfBlocks) * t_blockSize)))
	//{
		int bytesLeft = ((m_totalNrOfBlocks - m_currentBlock + 1) * t_blockSize) - (reinterpret_cast<char*>(m_head) - reinterpret_cast<char*>(m_poolPark->GetEndPointer()));
		bytesLeft = p_numBytes - bytesLeft;
		int neededBlocks = ceil((float)bytesLeft / (float)t_blockSize);
		for (size_t i = 0; i < neededBlocks; i++)
		{
			m_poolPark->GetNewMemoryBlockEndPoint();
			m_currentBlock--;
		}
	//}
	// Move head back in memory
	m_head = reinterpret_cast<char*>(m_head) - p_numBytes;
	return m_head;
}

void StackAllocatorInternal::Clear()
{
   m_head = m_startPointer;
}

void StackAllocatorInternal::ResetHeadTo(void* mempoint)
{
	m_head = mempoint;
	int t_blocksize = m_poolPark->GetMemoryBlockSize();
	// Check if we Reset past a blocks end point. If we do reevaluate the currentstackblock
	float shit = (reinterpret_cast<char*>(m_poolPark->GetEndPointer()) - reinterpret_cast<char*>(m_head));
	int t_potentialNewBlock = floor(shit / (float)t_blocksize);
	if (m_totalNrOfBlocks - m_currentBlock > t_potentialNewBlock)
	{
		m_currentBlock = m_totalNrOfBlocks - t_potentialNewBlock;
		m_poolPark->SetCurrentStackBlock(m_currentBlock);
	}
}

int StackAllocatorInternal::TestMethod()
{
    return 42;
}
    