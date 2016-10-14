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
	in our constructor. Will find the correct object to remove and send a signal to remove in the correct parser.
	*/
    bool FindAndForwardRemovableResource();
	/**
	*/
	void RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle);
	void AddToRemovableQueue(GUID p_id, size_t p_parserHandle);

private:
	PrioritizationManager(PrioritizationAlgorithm p_algo);
	~PrioritizationManager();
	static PrioritizationManager* m_singleton;
	Prioritization* m_prioritization;
	
};

