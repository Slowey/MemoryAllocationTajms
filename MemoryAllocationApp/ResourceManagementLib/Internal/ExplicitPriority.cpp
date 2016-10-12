#include "ExplicitPriority.h"

ExplicitPriority::ExplicitPriority()
{

}

ExplicitPriority::~ExplicitPriority()
{

}

void ExplicitPriority::UpdateMap(GUID p_id, size_t o_parserHandle)
{
    printf("I'm in updatemap in explicitprio. Nothing happens here. Remove this print if useless and spammy");
}

ParserUID ExplicitPriority::FindAndForwardRemovable()
{
    ParserUID t_parserUID;
    t_parserUID.guid = ERROR_GUID;
    printf("You ended up in priority management while running explicit freeing of resources. Will not free resource");
    return t_parserUID;
}
