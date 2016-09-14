#include <MemoryManager.h>
#include <PoolAllocator.h>
#include <iostream>
#include <TajmsLib.h>

int main()
{
    TajmsLib tajm;
    tajm.InitTajmsLib();
    float hasj = tajm.Test();
    // Create big ass memory manager (this should be a singleton)
    int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
    int forLoopTimerId2 = tajm.StartTimer("ForLoopTimer2");
    int forLoopTimerId3 = tajm.StartTimer("ForLoopTimer3");
    int forLoopTimerId4 = tajm.StartTimer("ForLoopTimer4");
    for (size_t i = 0; i < 4000000; i++)
    {
        int hej = 24;
    }
    tajm.StopTimer(forLoopTimerId1);
    tajm.StopTimer(forLoopTimerId4);
    tajm.StopTimer(forLoopTimerId2);
    //MemoryManager memManager;
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
    // tajm.ShutdownTajmsLib();
}