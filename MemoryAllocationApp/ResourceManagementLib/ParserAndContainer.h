#pragma once
#include <string>
#include "EnumsAndDefines.h"
class ParserAndContainer
{
public:
    // The file ending this parser wants to parse, should be without the '.'. for example "png"
    ParserAndContainer(std::string p_fileEndingToParse);
    ~ParserAndContainer();

    virtual void ParseAndSaveParsedData(void* p_dataStart, size_t p_size, GUID p_guid) = 0;
};

