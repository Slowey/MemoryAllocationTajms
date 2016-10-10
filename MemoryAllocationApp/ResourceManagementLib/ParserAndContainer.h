#pragma once
#include <string>
#include "EnumsAndDefines.h"
class ParserAndContainer
{
public:
    // The file ending this parser wants to parse, should be without the '.'. for example "png"
    ParserAndContainer(std::string p_fileEndingToParse);
    ~ParserAndContainer();

    // Dont delete the raw data, it might be used later!!
    virtual void ParseAndSaveParsedData(void* p_dataStart, size_t p_size, const GUID &p_guid) = 0;
    virtual bool ResourceExist(const GUID &p_guid) = 0;
    virtual void FreeResource(const GUID &p_guid) = 0; 
    void SetPriorityHandle(size_t p_priorityHandle) { m_priorityHandle = p_priorityHandle; };
private:
    size_t m_priorityHandle;
};

