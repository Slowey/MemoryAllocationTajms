#pragma once
#include "PoolAllocator.h"
#include "StackAllocator.h"

#define USE_LIBRARY

/**
Class used for all interaction with the memory library from an application.
To use the memory manager, one has to call MemoryManager::Get() first, to 
get a pointer to the memory manager (in accordance with the singleton pattern)

It is very important to initialize the memory library before using it
(calling Startup()). It is a singleton, but it has to be initialized before 
using (calling  MemoryManager::Get() without initializing is a bad idea).

The MemoryManager enables a developer to create his own allocators and
explicitly store data together closeby. This is done by calling the 
appropriate new overload (syntax below):
MyClass* instance = new(my_allocator)MyClass();

It also overloads new to use default segmented, general pools if no 
allocator is specified (syntax below):
MyClass* instance = new MyClass();

Finally it allows the user to explicitly allocate memory to the stack
using the following new overload (syntax below):
MyClass* instance = new(Stack::LongTerm)MyClass();

To clear the stack, the ClearStack() method is called
*/
class MemoryManager
{
public:

    /**
    Creates a pool allocator of desired segmentation and returns
    the pointer to it. In order to use the allocator, the appropriate
    new overload has to be made (see class documentation)*/
    PoolAllocator* CreatePoolAllocator(const int& p_segmentSize);

    /**
    Gets a pointer to the memory manager singleton. Make sure Startup has
    been called!*/
    static MemoryManager* Get();

    /**
    Clears the stack entierly. Pointers to data previously stored within
    the stack will obviously not longer be safe to use.*/
    void ClearStack();

    /**
    Starts the entire memory library and creates memory of the specified
    block size (in bytes), and p_numBlocks number of them. This effectively means
    p_blockSize * p_numBlocks bytes of memory*/
    static void Startup(const int & p_blockSize, const int & p_numBlocks);

	static void ResetTestThingy();

	static int GetTestThingy();



private:

    MemoryManager(const int & p_blockSize, const int & p_numBlocks);
    ~MemoryManager();
    static MemoryManager* m_singleton;

};

#ifdef USE_LIBRARY
// Don't actually need the ones that are not overrides ( new parameters) 
void* operator new[](size_t size, PoolAllocator* allocator);
void* operator new (size_t size, PoolAllocator* allocator);
void* operator new[](size_t size, Stack stackDuration);
void* operator new (size_t size, Stack stackDuration);
void* operator new (size_t size);
void operator delete(void* memBlock, PoolAllocator* allocator, size_t size);

#endif