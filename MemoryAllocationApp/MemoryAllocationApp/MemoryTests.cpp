#include "MemoryTests.h"
#include <vector>


MemoryTests::MemoryTests()
{
}


MemoryTests::~MemoryTests()
{
}

void MemoryTests::TestAllocateMany(double amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
    }
}

void MemoryTests::TestAllocateManyAndUse(double amount)
{
    int* lastInt = new int();
    *lastInt = 0;
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        *newInt = *lastInt + i;
        lastInt = newInt;
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

void MemoryTests::TestAllocateListAndUse(double amount)
{
    std::vector<int*> myVector;

    int* lastInt = new int();
    *lastInt = 0;
    for (size_t i = 0; i < amount; i++)
    {
        int* newInt = new int();
        *newInt = *lastInt + i;
        lastInt = newInt;
        myVector.push_back(newInt);
    }

    for (size_t i = 0; i < amount; i++)
    {
        *myVector[i] *= 1992;
    }
}
