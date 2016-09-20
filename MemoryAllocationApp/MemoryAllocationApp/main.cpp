

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
#define TEST_TO_RUN 1
std::mutex m;
void task1(std::string msg)
{
	m.lock();
	std::cout << "task1 says: " << msg << std::endl;
	m.unlock();
}
int main()
{
    TajmsLib tajm;

	//std::thread t1(task1, "Hello1");
	//std::thread t2(task1, "Hello2");
	//std::thread t4(task1, "Hello4");
	//std::thread t5(task1, "Hello5");
	//t1.join();
	//t2.join();
	//t5.join();
	//t4.join();
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
	int* derp = new(poolAllocator)int(5);
	TestClass* testClass = new(poolAllocator)TestClass();

	int* derp2 = new(Stack::LongTerm)int(5);


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