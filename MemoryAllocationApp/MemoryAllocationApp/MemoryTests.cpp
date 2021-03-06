#include "MemoryTests.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <future>

MemoryTests::MemoryTests()
{
	m_mutexTest = std::make_shared<std::mutex>();
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
void MemoryTests::SetStackRecursions(int nr_recursions)
{
	m_stackRecursions = nr_recursions;

}
// TEsta att inte deleta i funktionen utan att ist�llet resetta hela stacken efter helka skiten �r klar
void MemoryTests::TestStackRecursiveOurLib(int p_count)
{
	int* t_temp = new (Stack::ShortTerm)int(p_count);
	if(*t_temp < m_stackRecursions)
	{
		int* t_nextInt = new (Stack::ShortTerm)int(*t_temp+1);
		TestStackRecursiveOurLib(*t_nextInt);
	}
	operator delete (t_temp, Stack::LongTerm, sizeof(int));
}

// This method disappeared from header in a merge. Possibly not needed
//void MemoryTests::TestStackOS(int p_count)
//{
//	int t_temp = p_count;
//	if (t_temp < 100)
//	{
//		int t_nextInt = t_temp + 1;
//		TestStackOS(t_nextInt);
//	}
//}

void MemoryTests::TestStackRecursiveOS(int p_count)
{
	int t_temp = p_count;
	if (t_temp < m_stackRecursions)
	{
		int t_nextInt = t_temp + 1;
		TestStackRecursiveOS(t_nextInt);
	}
}

void MemoryTests::TestAllocateArrayStackOurLib(long p_amount)
{
	int* t_firstInt = new (Stack::ShortTerm)int(0);
	for (size_t i = 1; i < p_amount; i++)
	{
		int* t_ints = new (Stack::ShortTerm)int(i);

	}
	operator delete (t_firstInt, Stack::LongTerm, sizeof(int) * p_amount);
}

void MemoryTests::TestAllocateArrayStackOs(long p_amount)
{
	for (size_t i = 0; i < p_amount; i++)
	{
		int j = i;
		int* t_ints = reinterpret_cast<int*>(_malloca(sizeof(int)));
	}
}

void MemoryTests::TestAllocateArrayChunkStackOurLib(long p_amount)
{
	int* t_ints = new (Stack::ShortTerm)int[p_amount];
	operator delete (t_ints, Stack::LongTerm, sizeof(int) * (p_amount));
}

void MemoryTests::TestAllocateArrayChunkStackOs(long p_amount)
{
	int* t_ints = reinterpret_cast<int*>(_malloca(sizeof(int) * p_amount));
}

void MemoryTests::TestSpecificTestPre(long amount, long differentObjects)
{
    objectsWithObjects.resize(differentObjects);
    for (size_t i = 0; i < differentObjects; i++)
    {
        objectsWithObjects[i].resize(amount);
    }

    poolAllocator = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectOne));
    poolAllocatorTwo = MemoryManager::Get()->CreatePoolAllocator(sizeof(ObjectOne));
}

void MemoryTests::TestSpecificTestCaseAllocate(long amount, long differentObjects)
{
    /**
    Test
    Create different data types after each other

    Use type A sequentionally from array
    */

    //Allocate
    for (size_t i = 0; i < amount; i++)
    {
        objectsWithObjects[0][i] = new (poolAllocator) ObjectOne();

        for (size_t j = 1; j < differentObjects; j++)
        {
            objectsWithObjects[j][i] = new (poolAllocatorTwo) ObjectOne();
        }
    }
}

void MemoryTests::TestSpecificTestCaseUse(long amount)
{

    for (size_t i = 0; i < amount; i++)
    {
        objectsWithObjects[0][i]->Function();
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

void MemoryTests::MutexTestWithNoMutex()
{
	m_mutexTestInt++;
}

void MemoryTests::MutexTest()
{
	m_mutexTest->lock();
	m_mutexTestInt++;
	m_mutexTest->unlock();
}
void MemoryTests::PrintTestIntMutex()
{
	std::cout << m_mutexTestInt;
}

void MemoryTests::TestAllocateAndDeleteRandomly(double amount)
{
    std::vector<int*> numbers;
    numbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new (poolAllocator)int();
        numbers.push_back(newInt);
    }

    for (size_t i = 0; i < amount; i++)
    {
        operator delete (numbers[randomNumbers[i]], poolAllocator, sizeof(int));
    }
}

void MemoryTests::TestStack()
{






}



void MemoryTests::AllocateMatricesOnOsHeap(long p_amount)
{
	// create matrices
	std::vector<Matrix*> matrices;
	matrices.resize(p_amount);
	for (size_t i = 0; i < p_amount; i++)
	{
		matrices.at(i) = new Matrix();
	}

	// Use matrices
	for (size_t i = 0; i < p_amount; i+=2)
	{
		*matrices.at(i) * *matrices.at(i + 1);
	}

	// Delete matrices
	for (size_t i = 0; i < p_amount; i++)
	{
		delete matrices.at(i);
	}
}

void MemoryTests::AllocateMatricesOnOurStack(long p_amount)
{
	// create matrices
	std::vector<Matrix*> matrices;
	matrices.resize(p_amount);
	for (size_t i = 0; i < p_amount; i++)
	{
		matrices.at(i) = new (Stack::LongTerm)Matrix();
	}

	// use matrices
	for (size_t i = 0; i < p_amount; i+=2)
	{
		*matrices.at(i) * *matrices.at(i + 1);
	}

	operator delete (matrices.at(0), Stack::LongTerm, sizeof(matrices));	
}
