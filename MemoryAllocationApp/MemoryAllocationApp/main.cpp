

#include <iostream>
#include <TajmsLib.h>
#include "MemoryTests.h"
#include "LibDefines.h"

class TestClass
{
public:
	TestClass()
	{
		derp = 5;
		herp = 2.2f;
	}
	int derp;
	float herp;

};

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
    // Ask memory manager for an actual pool allocator with 32 segment size!!
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator(32);
    // Use pool allocator to varify it works
	int* derp = new(poolAllocator)int(5);
	TestClass* testClass = new(poolAllocator)TestClass();


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