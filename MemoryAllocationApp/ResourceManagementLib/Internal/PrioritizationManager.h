#pragma once
#include <malloc.h>
#include <new>
#include "../EnumsAndDefines.h"
class PrioritizationManager
{
public:
	/**
	Gets a pointer to the memory manager singleton. Make sure Startup has
	been called!*/
	static PrioritizationManager* Get();
	static void Startup(PrioritizationAlgorithm p_algo);

private:
	PrioritizationManager(PrioritizationAlgorithm p_algo);
	~PrioritizationManager();
	static PrioritizationManager* m_singleton;
};

