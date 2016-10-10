#pragma once
#include <map>
#include "../EnumsAndDefines.h"
#include <vector>
#include "Prioritization.h"
class PrioritizationManager
{
public:
	/**
	Gets a pointer to the memory manager singleton. Make sure Startup has
	been called!*/
	static PrioritizationManager* Get();
	static void Startup(PrioritizationAlgorithm p_algo);
	/**
	Calls the prioritization abstraction variable which was assigned a proper implementation
	in our constructor. 
	*/
	void UpdatePriority(GUID p_id, int& o_parserHandle);
    bool GetRemovableResource();

private:
	PrioritizationManager(PrioritizationAlgorithm p_algo);
	~PrioritizationManager();
	static PrioritizationManager* m_singleton;
	Prioritization* m_prioritization;
	std::vector<std::map<GUID, size_t>> m_parserList;
	
};

