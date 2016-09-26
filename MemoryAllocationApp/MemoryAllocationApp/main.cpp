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


int main(int numArgs, char * args[])
{
    MemoryManager::Startup(1024, 1000000);
    TajmsLib tajm;

    int testToRun = 5;
    int numObjects = 5;
    int seed = 33;
    
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
        else if (std::string("--seed").compare(args[i]) == 0)
        {
            i++;
            // Check if we got another arg
            if (i < numArgs)
            {
                seed = std::stoi(args[i]);
            }
        }
    }
 
    MemoryTests tests = MemoryTests();

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
        tests.CreateRandomAccessNumbers("randomNum", numObjects, seed);
        int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
        tests.TestAllocateAndDeleteRandomly(numObjects);
        tajm.StopTimer(forLoopTimerId1);
    }
	else if (testToRun == 5)
	{
#ifdef OURLIB
		std::string hej;
		int nrOfTests = 0;
		int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
		//while (nrOfTests)
		//{
		//	++nrOfTests;
			for (size_t i = 0; i < 10; i++)
			{

			//MemoryManager::Get()->ResetTestThingy();
			tests.TestThreadedAllocatorCreation();
			//int t_numberOFAllocators = MemoryManager::Get()->GetTestThingy();
			//if (t_numberOFAllocators > 802)
			//{
			//	std::cout << t_numberOFAllocators << std::endl;
			//	std::cin >> hej;
			//}
			//std::cout << "Test Nr: " << nrOfTests;
			//std::cout << " Nr of Allocs: " << t_numberOFAllocators << std::endl;
			}
		//}
		//std::cin >> hej;
		tajm.StopTimer(forLoopTimerId1);
#endif
	}
	else if (testToRun == 102)
	{
		std::mutex mLock;
		int amountOfTimes = 5000;
		int timerMutexLock = tajm.StartTimer("MutexLock");
		for (size_t i = 0; i < amountOfTimes; i++)
		{
			tests.MutexTest();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		//amountOfTimes = 0;
		//for (size_t i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTest();
		//}
		//amountOfTimes = 0;
		//for (size_t i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTest();
		//}
		//amountOfTimes = 0;
		//for (size_t i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTest();
		//}
		tajm.StopTimer(timerMutexLock);
		//tests.PrintTestIntMutex();
		//std::string hej = "";
		//std::cin >> hej;
	}
	else if (testToRun == 103)
	{
		unsigned long amountOfTimes = 5000;
		int timerWithoutMutexLock = tajm.StartTimer("WithoutMutexLock");
		for (unsigned long i = 0; i < amountOfTimes; i++)
		{
			tests.MutexTestWithNoMutex();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		//for (unsigned long i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTestWithNoMutex();
		//}
		//amountOfTimes = 0;
		//for (unsigned long i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTestWithNoMutex();
		//}
		//amountOfTimes = 0;
		//for (unsigned long i = 0; i < amountOfTimes; i++)
		//{
		//	tests.MutexTestWithNoMutex();
		//}
		tajm.StopTimer(timerWithoutMutexLock);
		//tests.PrintTestIntMutex();
		//std::string hej = "";
		//std::cin >> hej;
	}
    std::string testName = "";

    if (testToRun == 1)
    {
        testName = "AllocateMany_";
    }
    else if (testToRun == 2)
    {
        testName = "TestAllocateAndUseMatricesForFramesSpecific_";
    }
    else if (testToRun == 3)
    {
        testName = "TestAllocateAndDeleteMany_";
    }
    else if (testToRun == 4)
    {
        testName = "TestAllocateAndDeleteRandomly_";
    }
    else if (testToRun == 5)
    {
        testName = "ThreadedSimulator_";
    }
	else if (testToRun == 102)
	{
		testName = "MutexTiming_";
	}
	else if (testToRun == 103)
	{
		testName = "MutexTimingWithNoMutex_";
	}
    testName += std::to_string(numObjects);

    tajm.ShutdownTajmsLib(testName);
}