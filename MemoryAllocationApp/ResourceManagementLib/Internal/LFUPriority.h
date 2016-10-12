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
    void UpdateMap(GUID p_id, size_t p_parserHandle);
    ParserUID FindAndForwardRemovable();

private:
    std::map<size_t, std::map<GUID, size_t>>m_parserList;
};

