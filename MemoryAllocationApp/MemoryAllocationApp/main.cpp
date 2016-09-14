#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "TestClass.h"
#include <iostream>
#include <TajmsLib.h>


int main()
{
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();

     TajmsLib tajm;
     tajm.InitTajmsLib();
    // // Create big ass memory manager (this should be a singleton)
     int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
    // int forLoopTimerId2 = tajm.StartTimer("ForLoopTimer2");
    // int forLoopTimerId3 = tajm.StartTimer("ForLoopTimer3");
    // int forLoopTimerId4 = tajm.StartTimer("ForLoopTimer4");
    // for (size_t i = 0; i < 4000000; i++)
    // {
    //     int hej = 24;
    // }
    tajm.StopTimer(forLoopTimerId1);
    // tajm.StopTimer(forLoopTimerId4);
    // tajm.StopTimer(forLoopTimerId2);


    //MemoryManager memManager;

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
    // tajm.ShutdownTajmsLib();
}