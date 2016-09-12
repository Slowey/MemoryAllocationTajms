#include <MemoryManager.h>
#include <PoolAllocator.h>

int main()
{
    // Create big ass memory manager (this should be a singleton)
    MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = memManager.CreatePoolAllocator();
    // Use pool allocator to varify it works
    int test = poolAllocator->TestMethod();
    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
}