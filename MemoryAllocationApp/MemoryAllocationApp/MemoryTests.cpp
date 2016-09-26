#include "MemoryTests.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <future>

MemoryTests::MemoryTests()
{
}

MemoryTests::~MemoryTests()
{
}

void MemoryTests::CreateAllocator(size_t p_size)
{
    poolAllocator = MemoryManager::Get()->CreatePoolAllocator(p_size);
}

int randomFunc(int max) { return std::rand() % max; }

void MemoryTests::CreateRandomAccessNumbers( long amount, int seed)
{
    std::srand(seed);

    randomNumbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        randomNumbers.at(i) = i;
    }

    std::random_shuffle(randomNumbers.begin(), randomNumbers.end(), randomFunc);
}

// Test functions for generic

void MemoryTests::TestGenericAllocate(long amount)
{
    numbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        numbers[i] = newInt;
    }
}

void MemoryTests::TestGenericUseRandomly(long amount)
{
    for (size_t i = 0; i < amount - 1; i++)
    {
        *numbers[randomNumbers[i + 1]] += *numbers[randomNumbers[i]];
    }
}

void MemoryTests::TestGenericAllocateDifferentSizes(long amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newSmall1 = new int[1];
        int* newSmall2 = new int[2];
        int* newSmall3 = new int[3];
        int* newSmall4 = new int[4];
        int* newSmall5 = new int[5];
        int* newSmall6 = new int[6];
        int* newSmall7 = new int[7];
        int* newSmall8 = new int[8];
        int* newSmall9 = new int[16];
        int* newSmall10 = new int[32];
        int* newSmall11 = new int[64];
        int* newSmall12 = new int[128];
        int* newSmall13 = new int[256];
        int* newSmall14 = new int[512];
        int* newSmall15 = new int[1024];
        int* newSmall16 = new int[2048];
    }
}

void MemoryTests::TestGenericDelete(long amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        delete numbers[i];
    }
}

void MemoryTests::TestGenericDeleteRandomly(long amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        delete numbers[randomNumbers[i]];
    }
}

// Test for specific

void MemoryTests::TestSpecificAllocate(long amount)
{
    numbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        numbers[i] = newInt;
    }
}

void MemoryTests::TestSpecificUseRandomly(long amount)
{
    for (size_t i = 0; i < amount - 1; i++)
    {
        *numbers[randomNumbers[i + 1]] += *numbers[randomNumbers[i]];
    }
}

void MemoryTests::TestSpecificAllocateMatrices(long amount)
{
    matrices.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        Matrix* newMat = new (poolAllocator) Matrix();
        matrices[i] = newMat;
    }
}

void MemoryTests::TestSpecificUseMatrices(long amount)
{
    Matrix view = Matrix();
        
    for (size_t i = 0; i < amount; i++)
    {
        *matrices[i]*view;
    }
}

void MemoryTests::TestSpecificUseMatricesRandomly(long amount)
{
    Matrix view = Matrix();

    for (size_t i = 0; i < amount; i++)
    {
        *matrices[randomNumbers[i]] * view;
    }
}

void MemoryTests::TestSpecificDelete(long amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        operator delete(numbers.at(i), poolAllocator, sizeof(int));
    }
}

void MemoryTests::TestSpecificDeleteRandomly(long amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        operator delete (numbers[randomNumbers[i]], poolAllocator, sizeof(int));
    }
}

void MemoryTests::TestSpecificRandomyAllocateDelete(long amount)
{
    TestSpecificAllocate(amount);
    
    int count = amount / 2;
    for (size_t i = 0; i < count; i++)
    {
        operator delete (numbers[randomNumbers[i]], poolAllocator, sizeof(int));
    }

    for (size_t i = 0; i < count; i++)
    {
        int* newInt = new int();
    }
}
// TEsta att inte deleta i funktionen utan att istället resetta hela stacken efter helka skiten är klar
void MemoryTests::TestStackOurLib(int p_count)
{
	int* t_temp = new (Stack::ShortTerm)int(p_count);
	if(*t_temp < 100)
	{
		int* t_nextInt = new (Stack::ShortTerm)int(*t_temp+1);
		TestStackOurLib(*t_nextInt);
	}
	operator delete (t_temp, Stack::LongTerm, sizeof(int));
}


void MemoryTests::TestStackOS(int p_count)
{
    int t_temp = p_count;
    if (t_temp < 100)
    {
        int t_nextInt = t_temp + 1;
        TestStackOS(t_nextInt);
    }
}

void MemoryTests::TestSpecificTestPre(long amount)
{
    objectsOne.resize(amount);
    objectsTwo.resize(amount);
    objectsThree.resize(amount);
    objectsFour.resize(amount);

    poolAllocator = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectOne));
    poolAllocatorTwo = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectTwo));
    poolAllocatorThree = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectThree));
    poolAllocatorFour = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectFour));
}

void MemoryTests::TestSpecificTestCaseAllocate(long amount)
{
    /**
    Test
    Create different data types after each other

    Use type A sequentionally from array
    */

    //Allocate
    for (size_t i = 0; i < amount; i++)
    {
        objectsOne[i] = new (poolAllocator) ObjectOne();
        objectsTwo[i] = new (poolAllocator) ObjectTwo();
        objectsThree[i] = new (poolAllocator) ObjectThree();
        objectsFour[i] = new (poolAllocator) ObjectFour();
    }
}

void MemoryTests::TestSpecificTestCaseUse(long amount)
{
    // number of frames
    for (size_t i = 0; i < 60*10; i++)
    {
        for (size_t i = 0; i < amount; i++)
        {
            objectsOne[i]->Function();
        }

        for (size_t i = 0; i < amount; i++)
        {
            objectsOne[i]->Function();
        }

        for (size_t i = 0; i < amount; i++)
        {
            objectsOne[i]->Function();
        }

        for (size_t i = 0; i < amount; i++)
        {
            objectsOne[i]->Function();
        }
    }
}




void ThreadedAllocatorCreationExtension(int p_myInt, bool* p_goTime, std::promise<int> && o_result)//, int& o_endInt)
{
    /// Wait for all threads to be created
    //while (!*p_goTime)
    //{
    //}
    /// Create allocator and value using allocator
    PoolAllocator* t_poolAllocator = MemoryManager::Get()->CreatePoolAllocator(sizeof(int));
    int* t_myInt = new (t_poolAllocator)int(p_myInt);
    //Wait for all threads to be done allocating their ints
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // Read value and put as output
    //o_endInt = *t_myInt;
    //std::cout << *t_myInt << std::endl;
    o_result.set_value(*t_myInt);
    operator delete (t_myInt, t_poolAllocator, sizeof(int));
}
void EmptyShit()
{
    std::cout << "derp";
}
void MemoryTests::TestThreadedAllocatorCreation()
{
    using namespace std;
    //std::thread t2(task1, "Hello2");
    bool* t_threadTest = new bool(false);
    PoolAllocator* t_poolAllocator = MemoryManager::Get()->CreatePoolAllocator(sizeof(int));
    //int amountOfThreads = 10;
    int resultValue[800];
    std::promise<int> promiseVector[800];
    std::future<int> futureList[800];
    std::vector<std::thread> threadVector;
    std::string stringText = "No Error";
    for (size_t i = 0; i < 800; i++)
    {
        futureList[i] = promiseVector[i].get_future();
    }
    for (size_t i = 0; i < 800; i++)
    {
        //std::thread t(EmptyShit);

        threadVector.push_back(std::thread(&ThreadedAllocatorCreationExtension, i, t_threadTest, std::move(promiseVector[i])));

        //int h = f.get();
        //resultValue[i] = h;
        //std::future <int> ret = std::thread t_temp(ThreadedAllocatorCreationExtension, i, t_threadTest);
        //threadVector.push_back(thread(ThreadedAllocatorCreationExtension, i, t_threadTest, resultValue[i]));
        //threadVector.push_back(t_temp);
        //threadVector.push_back(thread(EmptyShit));
    }
    std::string hej;
    //std::cin >> hej;
    *t_threadTest = true;
    for (size_t i = 0; i < 800; i++)
    {
        threadVector[i].join();
    }
    for (size_t i = 0; i < 800; i++)
    {
        resultValue[i] = futureList[i].get();
    }
    for (size_t i = 0; i < 800; i++)
    {
        for (size_t j = 0; j < 800; j++)
        {
            if (i != j && resultValue[i] == resultValue[j])
            {
                stringText = "Error";
                std::cout << stringText << std::endl;
                //std::cin >> hej;
            }
        }
    }

    //std::cout << stringText << std::endl;
    //std::cin >> hej;
}