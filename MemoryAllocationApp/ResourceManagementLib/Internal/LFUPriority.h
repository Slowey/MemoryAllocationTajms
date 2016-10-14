#pragma once
#include <map>
#include "../EnumsAndDefines.h"
#include "PrioritizationManager.h"
#include "Prioritization.h"


class LFUPriority : public Prioritization
{
public:
    LFUPriority();
    ~LFUPriority();
    /*void UpdateMap(GUID p_id, size_t p_parserHandle);
    ParserUID FindAndForwardRemovable();*/

	void AddToRemovableQueue(GUID p_id, size_t p_parserHandle);
	ParserUID GetRemovableResource();
	void RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle);

private:
    std::map<size_t, std::map<GUID, size_t>>m_parserList;
};

