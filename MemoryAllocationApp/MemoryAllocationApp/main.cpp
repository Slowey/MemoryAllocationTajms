#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "TestClass.h"
#include <iostream>
#include "MemoryTests.h"

int main()
{
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();
    // Use pool allocator to varify it works

    MemoryTests tests = MemoryTests();
    tests.TestAllocateMany(10000);
    tests.TestAllocateManyAndUse(10000);
    tests.TestAllocateManyDifferent(10000);

    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
}