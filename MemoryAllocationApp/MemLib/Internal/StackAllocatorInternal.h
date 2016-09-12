#pragma once
#include "../StackAllocator.h"

class StackAllocatorInternal
    :StackAllocator
{
public:
    StackAllocatorInternal();
    ~StackAllocatorInternal();
    int TestMethod() override;
};