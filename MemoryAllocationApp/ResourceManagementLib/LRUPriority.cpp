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
    //Check to see if handle is legit. If not add to the list.
	if (o_parserHandle < 0)
	{
		std::map<GUID, size_t>t_newMap;
		m_parserList.push_back(t_newMap);
		o_parserHandle = m_parserList.size() - 1;
	}
    //Update all the aging values and set the used resource to 0.
	size_t t_loopLength = m_parserList.size() - 1;
	for (size_t i = 0; i < t_loopLength; i++)
	{
		for (auto iterator = m_parserList[i].begin(); iterator != m_parserList[i].end(); iterator++) {
			iterator->second += 1;
		}
	}
	m_parserList[o_parserHandle][p_id] = 0;
}

ParserUID LRUPriority::FindAndForwardRemovable()
{
    // Iterate to find the highest aging value. Return that GUID. Should also return what list the guid is in. TODO
	size_t t_leastRecentUsedValue = 0;
    ParserUID t_parserUID;
	size_t t_loopLength = m_parserList.size() - 1;
	for (size_t i = 0; i < t_loopLength; i++)
	{
		for (auto iterator = m_parserList[i].begin(); iterator != m_parserList[i].end(); iterator++) {
			if (iterator->second >= t_leastRecentUsedValue)
			{
				t_parserUID.guid = iterator->first;
                t_parserUID.parserHandle = i;
				t_leastRecentUsedValue = iterator->second;
			}
		}
	}
    return t_parserUID;
}
