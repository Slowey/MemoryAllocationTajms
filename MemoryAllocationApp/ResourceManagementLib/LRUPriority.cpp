#include "LRUPriority.h"


LRUPriority::LRUPriority(std::vector<std::map<GUID, size_t>>& p_list):
	m_parserList(p_list)
{
	
}
LRUPriority::~LRUPriority()
{
}
void LRUPriority::UpdateMap(GUID p_id, int& o_parserHandle)
{
	if (o_parserHandle < 0)
	{
		std::map<GUID, size_t>t_newMap;
		m_parserList.push_back(t_newMap);
		o_parserHandle = m_parserList.size() - 1;
	}
	size_t t_loopLength = m_parserList.size() - 1;
	for (size_t i = 0; i < t_loopLength; i++)
	{
		for (auto iterator = m_parserList[i].begin(); iterator != m_parserList[i].end(); iterator++) {
			iterator->second += 1;
		}
	}
	m_parserList[o_parserHandle][p_id] = 0;
}

GUID LRUPriority::GetRemovable()
{
	size_t t_leastRecentUsedValue = 0;
	GUID t_leastRecentlyUsedGUID = -1;
	size_t t_loopLength = m_parserList.size() - 1;
	for (size_t i = 0; i < t_loopLength; i++)
	{
		for (auto iterator = m_parserList[i].begin(); iterator != m_parserList[i].end(); iterator++) {
			if (iterator->second >= t_leastRecentUsedValue)
			{
				t_leastRecentlyUsedGUID = iterator->first;
				t_leastRecentUsedValue = iterator->second;
			}
		}
	}
	return t_leastRecentlyUsedGUID;
}
