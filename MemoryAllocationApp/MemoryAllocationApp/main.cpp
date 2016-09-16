

#include <iostream>
#include <TajmsLib.h>
#include "MemoryTests.h"
#include "LibDefines.h"
#include <string>

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
#define TEST_TO_RUN 1


int main()
{
    TajmsLib tajm;

    // Create big ass memory manager (this should be a singleton)

    //MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator();
    // Use pool allocator to varify it works
	int* derp = new(poolAllocator)int(5);
	TestClass* testClass = new(poolAllocator)TestClass();


    int numObjects = 100000;


    MemoryTests tests = MemoryTests();

#ifdef RUN_PRE_VALUES

    tests.CreateRandomAccessNumbers("randomNum", numObjects);

#elif RUN_NORMAL

    tests.LoadRandomAccessNumbers("randomNum", numObjects);
    tajm.InitTajmsLib();

#if TEST_TO_RUN == 1
    int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
    tests.TestAllocateMany(numObjects);
    tajm.StopTimer(forLoopTimerId1);


#elif TEST_TO_RUN == 2


    
#endif

    std::string testName = "";

    if (TEST_TO_RUN == 1)
    {
        testName = "test1";
    }
    else if (TEST_TO_RUN == 2)
    {
        testName = "test2";
    }
    else if (TEST_TO_RUN == 3)
    {
        testName = "test3";
    }
    else if (TEST_TO_RUN == 4)
    {
        testName = "test4";
    }
    else if (TEST_TO_RUN == 5)
    {
        testName = "test5";
    }

    tajm.ShutdownTajmsLib(testName);
#endif
}