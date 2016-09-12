#include "MemoryManager.h"
#include "Internal/PoolAllocatorInternal.h"

PoolAllocator * MemoryManager::CreatePoolAllocator()
{
    return new PoolAllocatorInternal();
}
