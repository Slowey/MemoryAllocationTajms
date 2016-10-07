#pragma once
#include "../EnumsAndDefines.h"
class Prioritization
{
public:
	virtual void UpdateMap(GUID p_id, int& o_parserHandle) = 0;
	virtual GUID GetRemovable() = 0;
};