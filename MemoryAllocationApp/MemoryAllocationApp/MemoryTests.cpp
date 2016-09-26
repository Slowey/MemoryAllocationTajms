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

void MemoryTests::TestStack()
{






}
