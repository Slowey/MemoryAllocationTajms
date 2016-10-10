#pragma once
#include <map>
#include "EnumsAndDefines.h"
#include "Internal/PrioritizationManager.h"
#include "Internal/Prioritization.h"
class FIFOPriority : public Prioritization
{
public:
    FIFOPriority(std::vector<std::map<GUID, size_t>>& p_parserList);
    ~FIFOPriority();
    void UpdateMap(GUID p_id, int& o_parserHandle);
    ParserUID FindAndForwardRemovable();


private:
    std::vector<std::map<GUID, size_t>>& m_parserList;
    size_t m_increment;
};