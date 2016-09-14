#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "TestClass.h"
#include <iostream>


int main()
{
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();
    // Use pool allocator to varify it works
    int test = poolAllocator->TestMethod();

    

	//TestClass testClass = TestClass();
	//testClass.TestAllocate();

    int* b = new int();
    int* a = new (poolAllocator) int();

    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
}