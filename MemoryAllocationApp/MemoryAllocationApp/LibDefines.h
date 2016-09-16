#pragma once
//#define OURLIB
#ifdef OURLIB  
#include <MemoryManager.h>
#include <PoolAllocator.h>
#pragma comment (lib, "MemLib.lib")
#else
#include "MemoryManagerDummy.h"
#endif