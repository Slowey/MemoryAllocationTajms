#pragma once
#include <map>
#include "EnumsAndDefines.h"
#include "Internal/PrioritizationManager.h"
#include "Internal/Prioritization.h"


class LRUPriority : public Prioritization
{
public:
	LRUPriority();
	~LRUPriority();
	void UpdateMap(GUID p_id, size_t p_parserHandle);
	ParserUID FindAndForwardRemovable();

private:
	std::map<size_t, std::map<GUID, size_t>>m_parserList;
};

