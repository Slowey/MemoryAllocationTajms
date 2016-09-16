#include "StackAllocatorInternal.h"
#include <string>

StackAllocatorInternal::StackAllocatorInternal(void * p_start)
	:m_startPointer(p_start), m_head(p_start)
{

}

StackAllocatorInternal::~StackAllocatorInternal()
{
}



StackAllocatorInternal * StackAllocatorInternal::Get()
{
	if (m_singleton == nullptr)
	{
		// Not initialized
		return nullptr;
	}
	return m_singleton;
}

void StackAllocatorInternal::Initialize(void* p_start)
{
	m_singleton = (StackAllocatorInternal*)malloc(sizeof(StackAllocatorInternal));
	new (m_singleton) StackAllocatorInternal(p_start);
}

void* StackAllocatorInternal::Allocate(size_t p_numBytes)
{
	// Move head back in memory
	m_head = reinterpret_cast<char*>(m_head) - p_numBytes;
	return m_head;
}

int StackAllocatorInternal::TestMethod()
{
    return 42;
}
    