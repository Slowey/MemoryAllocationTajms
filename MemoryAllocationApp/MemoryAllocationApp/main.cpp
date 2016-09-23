

#include <iostream>
#include <TajmsLib.h>
#include "MemoryTests.h"
#include "LibDefines.h"
#include <StackAllocator.h>
#include <string>
#include <thread>
#include <mutex>

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
#define TEST_TO_RUN 2

int main(int args[])
{
    MemoryManager::Startup(1024, 1000000);
    TajmsLib tajm;

    //MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator with 32 segment size!!
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator(32);
    // Use pool allocator to varify it works
    

	TestClass* testClass = new(poolAllocator)TestClass();

	int* derp2 = new(Stack::LongTerm)int(5);


    int numObjects = 100000;


    MemoryTests tests = MemoryTests();

#ifdef RUN_PRE_VALUES

    tests.CreateRandomAccessNumbers("randomNum", numObjects);

#elif RUN_NORMAL

    tests.LoadRandomAccessNumbers("randomNum", numObjects);
    tajm.InitTajmsLib();

    if (TEST_TO_RUN == 1)
    {
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateMany(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (TEST_TO_RUN == 2)
    {
        tests.CreateAllocator(sizeof(Matrix));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndUseMatricesForFramesSpecific(numObjects, 1);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (TEST_TO_RUN == 3)
    {
        tests.CreateAllocator(sizeof(Matrix));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndDeleteMany(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (TEST_TO_RUN == 4)
    {
        tests.CreateAllocator(sizeof(Matrix));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateThenDeleteRandomly(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }


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