#include "FIFOPriority.h"

FIFOPriority::FIFOPriority()
{
    m_increment = 0;
}

FIFOPriority::~FIFOPriority()
{

}

void FIFOPriority::AddToRemovableQueue(GUID p_id, size_t p_parserHandle)
{
}

ParserUID FIFOPriority::GetRemovableResource()
{
	return ParserUID();
}

void FIFOPriority::RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle)
{
}

//void FIFOPriority::UpdateMap(GUID p_id, size_t p_parserHandle)
//{
//    //Check to see if handle is legit. If not add to the list.
//    if (m_parserList.find(p_parserHandle) == m_parserList.end())
//    {
//        std::map<GUID, size_t>t_map;
//        m_parserList.insert(std::pair<size_t, std::map<GUID, size_t>>(p_parserHandle, t_map));
//        //m_parserList[p_parserHandle]; Testa TODO
//    }
//    // Check if the guid is already in the map. If not add it to the map and increment the variable.
//    if (m_parserList[p_parserHandle].insert(std::pair<GUID, size_t>(p_id, m_increment)).second)
//    {
//        // WARNING TODO If program runs very long this variable might reach its max and that will bork this algorithm. 
//        m_increment++;
//    }
//}

//ParserUID FIFOPriority::FindAndForwardRemovable()
//{
//    // Variables needed for this function
//    size_t t_length = m_parserList.size() - 1;
//    ParserUID t_parserUID;
//    t_parserUID.parserHandle = -1;
//    int t_lowestIterator = INT_MAX;
//    //Iterate over the list containing the different parsers maps. (We dont want to remove memory that a different parser is using. Two parsers can use the same memory and GUID but it is handled as two different objects
//    for (auto iterator1 = m_parserList.begin(); iterator1 != m_parserList.end(); iterator1++)
//    {
//        //Iterate over the parser map. Find the lowest iteratornumber (FIFO) and save the handles to it (List and GUID)
//        for (auto iterator2 = m_parserList[iterator1->first].begin(); iterator2 != m_parserList[iterator1->first].end(); iterator2++) {
//            if (iterator2->second < t_lowestIterator)
//            {
//                t_parserUID.guid = iterator2->first;
//                t_parserUID.parserHandle = iterator1->first;
//                t_lowestIterator = iterator2->second;
//            }
//        }
//    }
//    //Remove the guid from the map and return the GUID so someone else can free the resource.
//    m_parserList[t_parserUID.parserHandle].erase(t_parserUID.guid);
//    return t_parserUID;
//}
