#pragma once
#include "../EnumsAndDefines.h"
struct ParserUID
{
    GUID guid;
    size_t parserHandle;
};
class Prioritization
{
public:
	virtual void UpdateMap(GUID p_id, size_t p_parserHandle) = 0;
	virtual ParserUID FindAndForwardRemovable() = 0;

};