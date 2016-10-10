#pragma once
#include "../EnumsAndDefines.h"

class Prioritization
{
public:
	virtual void UpdateMap(GUID p_id, size_t p_parserHandle) = 0;
	virtual ParserUID FindAndForwardRemovable() = 0;

};