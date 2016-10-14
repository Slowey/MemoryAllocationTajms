#pragma once
#include <map>
#include "EnumsAndDefines.h"
#include "Internal/PrioritizationManager.h"
#include "Internal/Prioritization.h"
class FIFOPriority : public Prioritization
{
public:
    FIFOPriority();
    ~FIFOPriority();
    //void UpdateMap(GUID p_id, size_t p_parserHandle);
    //ParserUID FindAndForwardRemovable();

	void AddToRemovableQueue(GUID p_id, size_t p_parserHandle);
	ParserUID GetRemovableResource();
	void RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle);

private:
    std::map<size_t, std::map<GUID, size_t>>m_parserList;
    size_t m_increment;
};