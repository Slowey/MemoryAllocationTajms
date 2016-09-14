#include <MemoryManager.h>
#include <PoolAllocator.h>
#include <TajmsLib.h>

int main()
{
    TajmsLib tajm;
    tajm.InitTajmsLib();
    float hasj = tajm.Test();
    // Create big ass memory manager (this should be a singleton)
    int forLoopTimerId = tajm.StartTimer("ForLoopTimer");
    for (size_t i = 0; i < 4000000; i++)
    {
        int hej = 24;
    }
    tajm.StopTimer(forLoopTimerId);
    MemoryManager memManager;
    // Create an allocator pointer
    PoolAllocator* poolAllocator;
    // Ask memory manager for an actual pool allocator
    poolAllocator = memManager.CreatePoolAllocator();
    // Use pool allocator to varify it works
    int test = poolAllocator->TestMethod();
    // Silly int. Put a breakpoint here to ensure the program doesn't end (there are better ways of doing this but cba)
    int stop = 2;
    tajm.ShutdownTajmsLib();
}