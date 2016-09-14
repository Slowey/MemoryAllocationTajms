#pragma once


class MemoryTests
{
public:
    MemoryTests();
    ~MemoryTests();
    void TestAllocateMany(double amount);
    void TestAllocateManyAndUse(double amount);
    void TestAllocateManyDifferent(double amount);

    void TestAllocateListAndUse(double amount);
    
};

