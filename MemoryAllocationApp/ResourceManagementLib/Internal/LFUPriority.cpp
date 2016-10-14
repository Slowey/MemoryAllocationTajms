#include "LFUPriority.h"


LFUPriority::LFUPriority()
{
}
LFUPriority::~LFUPriority()
{
}
void LFUPriority::AddToRemovableQueue(GUID p_id, size_t p_parserHandle)
{
}
ParserUID LFUPriority::GetRemovableResource()
{
	return ParserUID();
}
void LFUPriority::RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle)
{
}
//void LFUPriority::UpdateMap(GUID p_id, size_t p_parserHandle)
//{
//    //Check to see if handle is legit. If not add to the list.
//    if (m_parserList.find(p_parserHandle) == m_parserList.end())
//    {
//        std::map<GUID, size_t>t_map;
//        m_parserList.insert(std::pair<size_t, std::map<GUID, size_t>>(p_parserHandle, t_map));
//        //m_parserList[p_parserHandle]; Testa TODO
//    }
//    
//    m_parserList[p_parserHandle][p_id]++;
//}
//
//ParserUID LFUPriority::FindAndForwardRemovable()
//{
//    // Iterate to find the highest aging value. Return that GUID. Should also return what list the guid is in. TODO
//    size_t t_leastFrequentlyUsedValue = SIZE_MAX;
//    ParserUID t_parserUID;
//    for (auto iterator1 = m_parserList.begin(); iterator1 != m_parserList.end(); iterator1++)
//    {
//        for (auto iterator2 = iterator1->second.begin(); iterator2 != iterator1->second.end(); iterator2++) {
//            if (iterator2->second <= t_leastFrequentlyUsedValue)
//            {
//                t_parserUID.guid = iterator2->first;
//                t_parserUID.parserHandle = iterator1->first;
//                t_leastFrequentlyUsedValue = iterator2->second;
//            }
//        }
//    }
//    return t_parserUID;
//}
