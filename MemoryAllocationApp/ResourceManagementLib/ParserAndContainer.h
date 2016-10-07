#pragma once
#include <string>
class ParserAndContainer
{
public:
    ParserAndContainer(std::string p_fileEndingToParse);
    ~ParserAndContainer();

    virtual void ParseAndSaveParsedData(void* p_dataStart, size_t p_size) = 0;
};

