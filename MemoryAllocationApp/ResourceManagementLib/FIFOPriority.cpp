#include "FIFOPriority.h"

FIFOPriority::FIFOPriority(std::vector<std::map<GUID, size_t>>& p_parserList)
    :m_parserList(p_parserList), m_increment(0)
{
    
}

FIFOPriority::~FIFOPriority()
{

}

void FIFOPriority::UpdateMap(GUID p_id, int & o_parserHandle)
{
    // Find out if this handle is assigned. If not add the parser to the list of parser
    if (o_parserHandle < 0)
    {
        std::map<GUID, size_t>t_newMap;
        m_parserList.push_back(t_newMap);
        o_parserHandle = m_parserList.size() - 1;
    }
    // Check if the guid is already in the map. If not add it to the map and increment the variable.
    if (m_parserList[o_parserHandle].insert(std::pair<GUID, size_t>(p_id, m_increment)).second)
    {
        // WARNING TODO If program runs very long this variable might reach its max and that will bork this algorithm. 
        m_increment++;
    }
}

ParserUID FIFOPriority::FindAndForwardRemovable()
{
    // Variables needed for this function
    size_t t_length = m_parserList.size() - 1;
    ParserUID t_parserUID;
    t_parserUID.parserHandle = -1;
    int t_lowestIterator = INT_MAX;
    //Iterate over the list containing the different parsers maps. (We dont want to remove memory that a different parser is using. Two parsers can use the same memory and GUID but it is handled as two different objects
    for (size_t i = 0; i < t_length; i++)
    {
        //Iterate over the parser map. Find the lowest iteratornumber (FIFO) and save the handles to it (List and GUID)
        for (auto iterator = m_parserList[i].begin(); iterator != m_parserList[i].end(); iterator++) {
            if (iterator->second < t_lowestIterator)
            {
                t_parserUID.guid = iterator->first;
                t_parserUID.parserHandle = i;
            }
        }
    }
    //Remove the guid from the map and return the GUID so someone else can free the resource.
    m_parserList[t_parserUID.parserHandle].erase(t_parserUID.guid);
    return t_parserUID;
}
