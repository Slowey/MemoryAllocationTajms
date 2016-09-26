#include "MemoryTests.h"
#include "../MemLib/StackAllocator.h"
#include <iostream>
#include <algorithm>



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
