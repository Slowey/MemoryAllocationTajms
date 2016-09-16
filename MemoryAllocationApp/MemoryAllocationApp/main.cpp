#include <MemoryManager.h>
#include <PoolAllocator.h>
#include <iostream>
#include <TajmsLib.h>
#include "MemoryTests.h"



//#define RUN_PRE_VALUES 1
#define RUN_NORMAL 2


int main()
{
    TajmsLib tajm;
    tajm.InitTajmsLib();

    // Create big ass memory manager (this should be a singleton)

    //MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();
    // Use pool allocator to varify it works

    int numObjects = 100000;


    MemoryTests tests = MemoryTests();

#ifdef RUN_PRE_VALUES

    tests.CreateRandomAccessNumbers("randomNum", numObjects);

#elif RUN_NORMAL

    tests.LoadRandomAccessNumbers("randomNum", numObjects);

    int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
    tests.TestAllocateMany(numObjects);
    tajm.StopTimer(forLoopTimerId1);

    int forLoopTimerId2 = tajm.StartTimer("ForLoopTimer2");
    tests.TestAllocateManyAndUse(numObjects);
    tajm.StopTimer(forLoopTimerId2);

    int forLoopTimerId3 = tajm.StartTimer("ForLoopTimer3");
    tests.TestAllocateManyDifferent(numObjects);
    tajm.StopTimer(forLoopTimerId3);

    tajm.ShutdownTajmsLib();
#endif
}