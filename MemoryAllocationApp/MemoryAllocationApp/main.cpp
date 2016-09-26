

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
#define TEST_TO_RUN 3
//std::shared_ptr <std::mutex> m;
//void task1(std::string msg)
//{
//	m->lock();
//	std::cout << "task1 says: " << msg << std::endl;
//	m->unlock();
//}
int main(int args[])
{
    MemoryManager::Startup(1024, 1000000);
    TajmsLib tajm;
	//m = std::make_shared<std::mutex>();
	//
	//std::thread t1(task1, "Hello1");
	//std::thread t2(task1, "Hello2");
	//std::thread t4(task1, "Hello4");
	//std::thread t5(task1, "Hello5");
	//t4.join();
	//t2.join();
	//t5.join();
	//t1.join();
	//std::cout << "TRÅDAR SENSEI RAMEN FOOOOOOOOOOOOOOOOOO JOINADE";
	//std::string hej2;
	//std::cin >> hej2;

    // Create big ass memory manager (this should be a singleton)


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
		int forLoopTimerId1 = tajm.StartTimer("ForLoopTimer1");
		std::string hej;
		int nrOfTests = 0;
		while (true)
		{
			++nrOfTests;

			MemoryManager::Get()->ResetTestThingy();
			tests.TestThreadedAllocatorCreation();
			int t_numberOFAllocators = MemoryManager::Get()->GetTestThingy();
			if (t_numberOFAllocators > 802)
			{
				std::cout << t_numberOFAllocators << std::endl;
				std::cin >> hej;
			}
			std::cout << "Test Nr: " << nrOfTests;
			std::cout << " Nr of Allocs: " << t_numberOFAllocators << std::endl;
		}
		std::cin >> hej;
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
        testName = "ThreadedSimulator";
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