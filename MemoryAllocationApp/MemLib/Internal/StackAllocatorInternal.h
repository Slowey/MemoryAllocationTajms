#pragma once
#include "../StackAllocator.h"

class StackAllocatorInternal
    :StackAllocator
{
public:
	static StackAllocatorInternal* Get();
	static void Initialize(void* p_start);
	void* Allocate(size_t p_numBytes);
    int TestMethod() override;

private:
	StackAllocatorInternal(void* p_start);
	~StackAllocatorInternal();

	/** 
	Pointer to the start of the stack, which is the 
	end of the memory*/
	void* m_startPointer;
	/**
	Pointer to the front/head of the stack.
	This will work backwards, which won't be
	visible outside the allocator, but it's worth
	mentioning.*/
	void* m_head;

	static StackAllocatorInternal* m_singleton;
};