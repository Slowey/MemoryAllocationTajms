#include "TestClass.h"

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

void TestClass::TestAllocate()
{
	int *a = new int();
	int *b = new int();
    BigStruct* stru = new BigStruct();
}
