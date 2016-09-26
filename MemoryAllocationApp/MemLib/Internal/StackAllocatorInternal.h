#pragma once
#include "../StackAllocator.h"
#include "PoolParkInternal.h"

/**
Stack used for the entire program. Operates as a stack
filling up memory from the end of the total memory allocated
with the initialization of the memory manager.*/
class StackAllocatorInternal
    :StackAllocator
{
public:
   // Singleton-get
	static StackAllocatorInternal* Get();
   // Initializes with the end of the total memory of the memory manager
	static void Initialize(void* p_start, PoolParkInternal* p_poolPark);
   // Allocates memory on the stack and returns a pointer to the memory
	void* Allocate(size_t p_numBytes);
   // Clears the entire stack by reseting the head pointer
   void Clear();
   void ResetHeadTo(void* mempoint);

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