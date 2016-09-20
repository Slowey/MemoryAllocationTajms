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
	if ((reinterpret_cast<char*>(m_head) - p_numBytes) < ((reinterpret_cast<char*>(m_poolPark->GetEndPointer()) + ((m_currentBlock-1) - m_totalNrOfBlocks) * t_blockSize)))
	{
		printf("Tried to allocate memory for stack but pool was full. So I snatched another pool");
		try {
			m_poolPark->GetNewMemoryBlockEndPoint();
		}
		catch (int e) {
			printf("Error %d Stack wasnt allowed to allocate memory", e);
		}
		m_currentBlock--;
	}
	// Move head back in memory
	m_head = reinterpret_cast<char*>(m_head) - p_numBytes;
	return m_head;
}

int StackAllocatorInternal::TestMethod()
{
    return 42;
}
    