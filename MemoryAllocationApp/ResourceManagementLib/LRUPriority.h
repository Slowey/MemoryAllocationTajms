#pragma once
#include <map>
#include "EnumsAndDefines.h"
#include "Internal/PrioritizationManager.h"
#include "Internal/Prioritization.h"


class LRUPriority : public Prioritization
{
public:
	LRUPriority(std::vector<std::map<GUID, size_t>>& p_parserList);
	~LRUPriority();
	void UpdateMap(GUID p_id, int& o_parserHandle);
	GUID GetRemovable();

private:
	std::vector<std::map<GUID, size_t>>& m_parserList;
};

