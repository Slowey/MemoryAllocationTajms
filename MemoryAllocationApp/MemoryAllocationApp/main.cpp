#include <iostream>
#include <TajmsLib.h>
#include "MemoryTests.h"
#include "LibDefines.h"
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

    int testToRun = 16;
    int numObjects = 10000;
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
        int ID = tajm.StartTimer("1");
        tests.TestGenericAllocate(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 2)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.TestGenericAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestGenericUseRandomly(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 3)
    {
        int ID = tajm.StartTimer("1");
        tests.TestGenericAllocateDifferentSizes(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 4)
    {
        tests.TestGenericAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestGenericDelete(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 5)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.TestGenericAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestGenericDeleteRandomly(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 6)
    {
        tests.CreateAllocator(sizeof(int));

        int ID = tajm.StartTimer("1");
        tests.TestSpecificAllocate(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 7)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.CreateAllocator(sizeof(int));
        tests.TestSpecificAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificUseRandomly(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 8)
    {
        tests.CreateAllocator(sizeof(Matrix));

        int ID = tajm.StartTimer("1");
        tests.TestSpecificAllocateMatrices(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 9)
    {
        tests.CreateAllocator(sizeof(Matrix));
        tests.TestSpecificAllocateMatrices(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificUseMatrices(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 10)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.CreateAllocator(sizeof(Matrix));
        tests.TestSpecificAllocateMatrices(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificUseMatricesRandomly(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 11)
    {
        tests.CreateAllocator(sizeof(int));
        tests.TestSpecificAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificDelete(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 12)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.CreateAllocator(sizeof(int));
        tests.TestSpecificAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificDeleteRandomly(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 13)
    {
        tests.CreateRandomAccessNumbers(numObjects, seed);
        tests.CreateAllocator(sizeof(int));
        tests.TestSpecificAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificRandomyAllocateDelete(numObjects);
        tajm.StopTimer(ID);
    }
    else if (testToRun == 16)
    {
        tests.TestSpecificTestPre(numObjects);
        tests.TestSpecificTestCaseAllocate(numObjects);

        int ID = tajm.StartTimer("1");
        tests.TestSpecificTestCaseUse(numObjects);
        tajm.StopTimer(ID);
    }
	else if (testToRun == 25)
	{
#ifdef OURLIB
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
#endif
	}


    std::string testName = "";

    if (testToRun == 1)
    {
        testName = "TestGenericAllocate_";
    }
    else if (testToRun == 2)
    {
        testName = "TestGenericUseRandomly_";
    }
    else if (testToRun == 3)
    {
        testName = "TestGenericAllocateDifferentSizes_";
    }
    else if (testToRun == 4)
    {
        testName = "TestGenericDelete_";
    }
    else if (testToRun == 5)
    {
        testName = "TestGenericDeleteRandomly_";
    }
    else if (testToRun == 6)
    {
        testName = "TestSpecificAllocate_";
    }
    else if (testToRun == 7)
    {
        testName = "TestSpecificUseRandomly_";
    }
    else if (testToRun == 8)
    {
        testName = "TestSpecificAllocateMatrices_";
    }
    else if (testToRun == 9)
    {
        testName = "TestSpecificUseMatrices_";
    }
    else if (testToRun == 10)
    {
        testName = "TestSpecificUseMatricesRandomly_";
    }
    else if (testToRun == 11)
    {
        testName = "TestSpecificDelete_";
    }
    else if (testToRun == 12)
    {
        testName = "TestSpecificDeleteRandomly_";
    }
    else if (testToRun == 13)
    {
        testName = "TestSpecificRandomyAllocateDelete_";
    }
    else if (testToRun == 14)
    {
        testName = "";
    }
    else if (testToRun == 16)
    {
        testName = "TestSpecificTestCaseUse_";
    }
    else if (testToRun == 25)
    {
        testName = "ThreadedSimulator";
    }

    testName += std::to_string(numObjects);

    tajm.ShutdownTajmsLib(testName);
}