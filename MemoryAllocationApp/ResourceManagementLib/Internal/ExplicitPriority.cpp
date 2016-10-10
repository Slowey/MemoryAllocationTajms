#include "ExplicitPriority.h"

ExplicitPriority::ExplicitPriority(std::vector<std::map<GUID, size_t>>& p_parserList)
    :m_parserList(p_parserList)
{

}

ExplicitPriority::~ExplicitPriority()
{

}

void ExplicitPriority::UpdateMap(GUID p_id, int & o_parserHandle)
{
    printf("I'm in updatemap in explicitprio. Nothing happens here. Remove this print if useless and spammy");
}

ParserUID ExplicitPriority::FindAndForwardRemovable()
{
    ParserUID t_parserUID;
    t_parserUID.guid = -1;
    printf("You ended up in priority management while running explicit freeing of resources. Will not free resource");
    return t_parserUID;
}
