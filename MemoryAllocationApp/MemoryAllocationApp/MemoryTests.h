#pragma once
#include <string>
#include <vector>

class MemoryTests
{
public:
    MemoryTests();
    ~MemoryTests();
    void CreateRandomAccessNumbers(std::string fileName, int amount);
    void LoadRandomAccessNumbers(std::string fileName, int amount);
    void TestAllocateMany(double amount);
    void TestAllocateManyAndUse(double amount);
    void TestAllocateManyDifferent(double amount);

    void TestAllocateListAndUse(double amount);

    std::vector<int> randomNumbers;
};

