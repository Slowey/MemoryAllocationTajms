#include "TestClass.h"
#include "TestClass2.h"
//#include <MemoryManager.h>

struct BigStruct
{
    int a, b;
};

TestClass::TestClass()
{
}


TestClass::~TestClass()
{
}

void TestAllocate()
{
    //PoolAllocator* allocator = MemoryManager::Get()->CreatePoolAllocator();
    //int* a = new (allocator) int();

    TestClass2 class2 = TestClass2();
    class2.TestAllocate();

	int *b = new int();
    BigStruct* stru = new BigStruct();
}
