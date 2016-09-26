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

void MemoryTests::CreateRandomAccessNumbers(std::string fileName, double amount, int seed)
{
    std::srand(seed);

    randomNumbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        randomNumbers.at(i) = i;
    }

    std::random_shuffle(randomNumbers.begin(), randomNumbers.end(), randomFunc);
}

void MemoryTests::LoadRandomAccessNumbers(std::string fileName, double amount)
{
    FILE* openFile;
    fopen_s(&openFile, fileName.c_str(), "rb");

    randomNumbers.resize(amount);
    fread(&randomNumbers[0], sizeof(int), amount, openFile);

    fclose(openFile);
}

// Test functions

void MemoryTests::TestAllocateMany(double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
    }
}

void MemoryTests::TestAllocateListAndUseRandomly(double amount)
{
    std::vector<int*> myVector;
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        myVector.push_back(newInt);
    }

    for (size_t i = 0; i < amount - 1; i++)
    {
        *myVector[randomNumbers[i + 1]] += *myVector[randomNumbers[i]];
    }
}



void MemoryTests::TestAllocateManyDifferent(double amount)
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

// Test for specific

void MemoryTests::TestAllocateMatricesForFramesSpecific(double amount, int frames)
{
    for (size_t i = 0; i < frames; i++)
    {
        std::vector<Matrix*> matrices;
        for (size_t i = 0; i < amount; i++)
        {
            Matrix* newMat = new (poolAllocator) Matrix();
            matrices.push_back(newMat);
        }
    }
}

void MemoryTests::TestAllocateAndUseMatricesForFramesSpecific(double amount, int frames)
{
    for (size_t i = 0; i < frames; i++)
    {
        std::vector<Matrix*> matrices;
        for (size_t i = 0; i < amount; i++)
        {
            Matrix* newMat = new (poolAllocator) Matrix();
            matrices.push_back(newMat);
        }

        Matrix view = Matrix();
        

        for (size_t i = 0; i < amount; i++)
        {
            *matrices[i]*view;
        }
    }
}

void MemoryTests::TestAllocateAndDeleteMany(long amount)
{
    std::vector<int*> numbers;
    numbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new (poolAllocator)int(i);
        numbers[i] = newInt;
    }
    for (size_t i = 0; i < amount; i++)
    {
        operator delete(numbers.at(i), poolAllocator, sizeof(int));
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
			if (i!=j && resultValue[i] == resultValue[j])
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
