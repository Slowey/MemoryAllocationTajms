#include "MemoryManager.h"
#include "Internal/AllocatorManager.h"
#include "Internal/StackAllocatorInternal.h"
#include <iostream>


MemoryManager* MemoryManager::m_singleton = nullptr;

MemoryManager::MemoryManager(const int &p_blockSize, const int &p_numBlocks)
{
    AllocatorManager::Startup(p_blockSize, p_numBlocks);
}

MemoryManager::~MemoryManager()
{
}

MemoryManager * MemoryManager::Get()
{
    return m_singleton;
}

void MemoryManager::ClearStack()
{
   StackAllocatorInternal::Get()->Clear();
}

void MemoryManager::Startup(const int &p_blockSize, const int &p_numBlocks)
{
    if (m_singleton != nullptr)
    {
        return;
    }
    m_singleton = (MemoryManager*)malloc(sizeof(MemoryManager));
    new (m_singleton) MemoryManager(p_blockSize, p_numBlocks);
}

void MemoryManager::ResetTestThingy()
{
	AllocatorManager::Get()->ResetTestThingy();
}

int MemoryManager::GetTestThingy()
{
	return AllocatorManager::Get()->GetTestThingy();
}

PoolAllocator * MemoryManager::CreatePoolAllocator(const int& p_segmentSize)
{
    return AllocatorManager::Get()->CreatePoolAllocator(p_segmentSize);
}
#ifdef USE_LIBRARY

struct AllocHeader
{
    uint32_t memorySize;
};

// When we use explicit use of allocators in allocation, we ignore the step of keeping track of allocator
void* operator new[] (size_t size, PoolAllocator* allocator)
{
    void* outpointer = operator new (size, allocator);
    return outpointer;
}

void* operator new (size_t size, PoolAllocator* allocator)
{
    void* outPointer = allocator->Allocate();

    return outPointer;
}

void * operator new[](size_t size, Stack stackDuration)
{
	// Should use stackduration in the future
	return StackAllocatorInternal::Get()->Allocate(size);
}

void * operator new(size_t size, Stack stackDuration)
{
	// Should use stackduration in the future
	return StackAllocatorInternal::Get()->Allocate(size);
}

void* operator new (size_t size)
{	
    size += sizeof(AllocHeader);

    PoolAllocator* allocator = nullptr;
    char* recvPointer = nullptr;
    void* outPointer = nullptr;
    // Choose pool to allocate depending on size
    if (size <= 4)
    {
        allocator = AllocatorManager::Get()->GetDefault4BytePool();
    }
    //else if (size <= 8)
    //{
    //    allocator = AllocatorManager::Get()->GetDefault8BytePool();
    //}
    //else if (size <= 16)
    //{
    //    allocator = AllocatorManager::Get()->GetDefault16BytePool();
    //}


    // Allocate from correct pool
    if (allocator != nullptr)
    {
        recvPointer = (char*)operator new (size, allocator);
        
    }
    else
    {
        recvPointer = (char*)malloc(size);
    }

    AllocHeader* header = (AllocHeader*)(recvPointer);
    header->memorySize = size;
    outPointer = recvPointer + sizeof(AllocHeader);
        
	return outPointer;
}

void operator delete(void* memBlock, PoolAllocator* allocator, size_t size)
{
    allocator->Deallocate(memBlock, size);
}

void operator delete(void* resetPoint, Stack stackDuration, size_t size)
{
	StackAllocatorInternal::Get()->ResetHeadTo(reinterpret_cast<char*>(resetPoint) + (size));
}

void operator delete (void* memBlock)
{
    AllocHeader* header = (AllocHeader*)(((char*)memBlock) - sizeof(AllocHeader));
    
    PoolAllocator* allocator = nullptr;

    if (header->memorySize <= 4)
    {
        allocator = AllocatorManager::Get()->GetDefault4BytePool();
    }
    //else if (header->memorySize <= 8)
    //{
    //    allocator = AllocatorManager::Get()->GetDefault8BytePool();
    //}
    //else if (header->memorySize <= 16)
    //{
    //    allocator = AllocatorManager::Get()->GetDefault16BytePool();
    //}

    if (allocator != nullptr)
    {
        operator delete(header, allocator, header->memorySize);
    }
    else
    {
        free(header);
    }
}

#endif