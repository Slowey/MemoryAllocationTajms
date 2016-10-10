#pragma once
#include <map>
#include "../EnumsAndDefines.h"
#include "PrioritizationManager.h"
#include "Prioritization.h"
class ExplicitPriority : public Prioritization
{
    /**
    This class is supposed to give the user the full access to removal logic instead of using priority algoritms
    */
public:
    ExplicitPriority(std::vector<std::map<GUID, size_t>>& p_parserList);
    ~ExplicitPriority();
    void UpdateMap(GUID p_id, int& o_parserHandle);
    GUID GetRemovable();


private:
    std::vector<std::map<GUID, size_t>>& m_parserList;
    size_t m_increment;
};
