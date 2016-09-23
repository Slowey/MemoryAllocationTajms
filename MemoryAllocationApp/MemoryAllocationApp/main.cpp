

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

int main(int numArgs, char * args[])
{
    MemoryManager::Startup(1024, 1000000);
    TajmsLib tajm;

    int testToRun = 3;
    int numObjects = 100000;
    
    // Parse args
    for (size_t i = 1; i < numArgs; i++)
    {
        if (std::string("--test").compare(args[i]) == 0)
        {
            i++;
            // Check if we got another arg
            if (i < numArgs)
            {
                testToRun = std::stoi(args[i]);
                
            }
        }
        else if (std::string("--num").compare(args[i]) == 0)
        {
            i++;
            // Check if we got another arg
            if (i < numArgs)
            {
                numObjects = std::stoi(args[i]);
            }
        }
    }
 
    MemoryTests tests = MemoryTests();
#ifdef RUN_PRE_VALUES

    tests.CreateRandomAccessNumbers("randomNum", numObjects);

#elif RUN_NORMAL

    tests.LoadRandomAccessNumbers("randomNum", numObjects);
    tajm.InitTajmsLib();

    if (testToRun == 1)
    {
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateMany(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (testToRun == 2)
    {
        tests.CreateAllocator(sizeof(Matrix));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndUseMatricesForFramesSpecific(numObjects, 1);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (testToRun == 3)
    {
        tests.CreateAllocator(sizeof(int));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndDeleteMany(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }
    else if (testToRun == 4)
    {
        tests.CreateAllocator(sizeof(int));
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndDeleteRandomly(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }


    std::string testName = "";

    if (testToRun == 1)
    {
        testName = "test1";
    }
    else if (testToRun == 2)
    {
        testName = "test2";
    }
    else if (testToRun == 3)
    {
        testName = "test3";
    }
    else if (testToRun == 4)
    {
        testName = "test4";
    }
    else if (testToRun == 5)
    {
        testName = "test5";
    }

    tajm.ShutdownTajmsLib(testName);
#endif
}