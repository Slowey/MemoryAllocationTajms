#include "ExplicitPriority.h"

ExplicitPriority::ExplicitPriority(std::vector<std::map<GUID, size_t>>& p_parserList)
    :m_parserList(p_parserList), m_increment(0)
{

}

ExplicitPriority::~ExplicitPriority()
{

}

void ExplicitPriority::UpdateMap(GUID p_id, int & o_parserHandle)
{
}

GUID ExplicitPriority::GetRemovable()
{
    return GUID();
}
