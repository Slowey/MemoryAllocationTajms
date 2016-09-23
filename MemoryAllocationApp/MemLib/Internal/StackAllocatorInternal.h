#pragma once
#include "../StackAllocator.h"
#include "PoolParkInternal.h"

class StackAllocatorInternal
    :StackAllocator
{
public:
	static StackAllocatorInternal* Get();
	static void Initialize(void* p_start, PoolParkInternal* p_poolPark);
	void* Allocate(size_t p_numBytes);
   void Clear();

    int TestMethod() override;

private:
	StackAllocatorInternal(void* p_start, PoolParkInternal* p_poolPark);
	~StackAllocatorInternal();
	PoolParkInternal* m_poolPark;
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
	/**
	The current block used by the stack. 
	Used to check if I am trying to allocate memory that does not belong to me
	*/
	int m_currentBlock;
	/**
	The number of blocks allocated in the whole pool
	*/
	int m_totalNrOfBlocks;
	static StackAllocatorInternal* m_singleton;
};