#pragma once
#include "DynamicList.h"
#include <mutex>

class PoolParkInternal
{
public:
    PoolParkInternal();
    /** 
    @param1 - size in bytes of one memory block
    @param2 - number of memory blocks to create

    param1 * param2 = total allocated size in bytes
    */
    PoolParkInternal(const int& p_memoryBlockSize, const int& p_numberOfMemoryBlocks);
    ~PoolParkInternal();

    /**
    @Return - a void pointer to where the blocks memory starts
    @throw - 1337 error (int) if tries to allocate where stack is operating
    */
    void* GetNewMemoryBlockStartPoint();
    /**
    @desc - Puts the given pointer in the free blocks queue meaning that the whole block
    , from @param1 to @param1 + memory block size, will be given to the next pool- or stack allocator that
    requests a new memory block. 
    @param1 - the void pointer given when GetNewMemoryBlockStartPoint was called
    */
	/**
	Same functionality as GetNewMemoryBlockStartPoint() but works for the stack. Returns the lastblock that is not yet allocated and gives it to the stack
	@throw - 1337 error (int) tried to allocated memory where heap is operating. (Out of memory)
	*/
	void* GetNewMemoryBlockEndPoint();
    void FreeMemoryBlock(void* p_blockStartPointer);

	/**
	Returns pointer to end of pool park*/
	void* GetEndPointer();
	int GetMemoryBlockSize();

	int GetCurrentStackBlock();

	void SetCurrentStackBlock(int p_newCurrentStackBlock);

    const int& GetMemoryBlockSize() const { return m_memoryBlockSize; };
	std::shared_ptr<std::mutex> m_mutexLockFree;	
	std::shared_ptr<std::mutex> m_mutexLockCreateNew;
private:
    MemLib::OwnVector<void*> m_freedBlocks;
    int m_currentBlock;
    void* m_startOfMemory;
    int m_memoryBlockSize;
    // Used to ensure we dont go outside the 
    int m_numberOfMemoryBlocks;
	//StackSpecific
	int m_currentStackBlock;
};