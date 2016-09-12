#pragma once
#include "PoolAllocator.h"

class MemoryManager
{
public:

    PoolAllocator* CreatePoolAllocator();

    static MemoryManager* Get();


private:
    MemoryManager();
    ~MemoryManager();
    static MemoryManager* m_singleton;
};

