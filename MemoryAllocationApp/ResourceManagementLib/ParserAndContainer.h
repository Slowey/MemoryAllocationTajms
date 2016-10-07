#pragma once
#include <string>
#include "EnumsAndDefines.h"
class ParserAndContainer
{
public:
    ParserAndContainer(std::string p_fileEndingToParse);
    ~ParserAndContainer();

    virtual void ParseAndSaveParsedData(void* p_dataStart, size_t p_size, GUID p_guid) = 0;
};

