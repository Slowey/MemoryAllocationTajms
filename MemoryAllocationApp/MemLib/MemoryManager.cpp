#include "MemoryManager.h"


int TestMethod()
{
	int *a = new int();
    return 42;
}

#include <iostream>
void* operator new(size_t size)
{
	std::cout << "Allocating!" << std::endl;

return malloc(size);
}