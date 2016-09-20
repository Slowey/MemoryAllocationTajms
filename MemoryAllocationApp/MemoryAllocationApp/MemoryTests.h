#pragma once
#include <string>
#include <vector>

class MemoryTests
{
public:
    MemoryTests();
    ~MemoryTests();
    void CreateRandomAccessNumbers(std::string fileName, double amount);
    void LoadRandomAccessNumbers(std::string fileName, double amount);
    void TestAllocateMany(double amount);
    void TestAllocateListAndUseRandomly(double amount);
    void TestAllocateThenDeleteRandomly(double amount);
    void TestAllocateManyDifferent(double amount);

    void TestAllocateMatricesForFramesSpecific(double amount, int frames);

    void TestAllocateAndUseMatricesForFramesSpecific(double amount, int frames);

    void TestAllocateAndDeleteMany(long amount);

    std::vector<int> randomNumbers;
    std::vector<int> numbers;
};

