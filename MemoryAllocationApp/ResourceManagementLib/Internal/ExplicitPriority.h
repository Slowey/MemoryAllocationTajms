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
    ExplicitPriority();
    ~ExplicitPriority();
    //void UpdateMap(GUID p_id, size_t o_parserHandle);
    //ParserUID FindAndForwardRemovable();

	void AddToRemovableQueue(GUID p_id, size_t p_parserHandle);
	ParserUID GetRemovableResource();
	void RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle);

private:
};
