#include "MemoryTests.h"

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

// Test functions for generic

void MemoryTests::TestGenericAllocate(double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
    }
}

void MemoryTests::TestGenericAllocateAndUseRandomly(double amount)
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



void MemoryTests::TestGenericAllocateDifferentSizes(double amount)
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

void MemoryTests::TestSpecificAllocate(double amount)
{
    numbers.resize(amount);
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        numbers.push_back(newInt);
    }
}

void MemoryTests::TestSpecificAllocateMatrices(double amount)
{
    std::vector<Matrix*> matrices;
    for (size_t i = 0; i < amount; i++)
    {
        Matrix* newMat = new (poolAllocator) Matrix();
        matrices.push_back(newMat);
    }
}

void MemoryTests::TestSpecificAllocateAndUseMatrices(double amount)
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

void MemoryTests::TestSpecificAllocateAndUseMatricesRandomly(double amount)
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