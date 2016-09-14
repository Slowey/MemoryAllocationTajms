#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "TestClass.h"
#include <iostream>


int main()
{
    TajmsLib tajm;
    tajm.InitTajmsLib();
    float hasj = tajm.Test();
    // Create big ass memory manager (this should be a singleton)
    int forLoopTimerId = tajm.StartTimer("ForLoopTimer");
    for (size_t i = 0; i < 4000000; i++)
    {
        int hej = 24;
    }
    tajm.StopTimer(forLoopTimerId);
    MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();
    // Use pool allocator to varify it works
    int test = poolAllocator->TestMethod();

    int* o = new (poolAllocator)int[300]();

	TestClass* testClass = new TestClass();
	//testClass->TestAllocate();
    TestAllocate();
    int* b = new int();
    int* a = new (poolAllocator) int();

    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
    tajm.ShutdownTajmsLib();
}