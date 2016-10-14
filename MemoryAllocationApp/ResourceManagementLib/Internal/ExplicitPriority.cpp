#include "ExplicitPriority.h"

ExplicitPriority::ExplicitPriority()
{

}

ExplicitPriority::~ExplicitPriority()
{

}

void ExplicitPriority::AddToRemovableQueue(GUID p_id, size_t p_parserHandle)
{
	printf("I'm in AddToRemovableQueue in explicitprio. Nothing happens here. Remove this print if useless and spammy");
}

ParserUID ExplicitPriority::GetRemovableResource()
{
	ParserUID t_parserUID;
	t_parserUID.guid = ERROR_GUID;
	printf("You ended up in priority management while running explicit freeing of resources. Will not free resource");
	return t_parserUID;
}

void ExplicitPriority::RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle)
{
	printf("I'm in RemoveFromRemovableQueue in explicitprio. Nothing happens here. Remove this print if useless and spammy");
}

//void ExplicitPriority::UpdateMap(GUID p_id, size_t o_parserHandle)
//{
//    printf("I'm in updatemap in explicitprio. Nothing happens here. Remove this print if useless and spammy");
//}

//ParserUID ExplicitPriority::FindAndForwardRemovable()
//{
//    ParserUID t_parserUID;
//    t_parserUID.guid = ERROR_GUID;
//    printf("You ended up in priority management while running explicit freeing of resources. Will not free resource");
//    return t_parserUID;
//}
