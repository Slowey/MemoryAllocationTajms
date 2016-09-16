

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
	int* derp = new(poolAllocator)int(5);
	TestClass* testClass = new(poolAllocator)TestClass();


    MemoryTests tests = MemoryTests();
    int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
    tests.TestAllocateMany(100000);
    tajm.StopTimer(forLoopTimerId1);

    int forLoopTimerId2 = tajm.StartTimer("ForLoopTimer2");
    tests.TestAllocateManyAndUse(100000);
    tajm.StopTimer(forLoopTimerId2);

    int forLoopTimerId3 = tajm.StartTimer("ForLoopTimer3");
    tests.TestAllocateManyDifferent(100000);
    tajm.StopTimer(forLoopTimerId3);

    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
    tajm.ShutdownTajmsLib();
}