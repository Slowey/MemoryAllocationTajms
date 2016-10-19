#pragma once
class ParserAndContainer;
#include "EnumsAndDefines.h"
#include <unordered_map>
#include <string>
#include <vector>

class ParserAndContainerManager
{
public:
    ParserAndContainerManager();
    ~ParserAndContainerManager();

    // Initializes the singleton
    static void Initialize();
    //Returns the singleton
    static ParserAndContainerManager& Get();
    // A function that adds the parser to a map. The file ending indicates which files the parser wants to parse
    void InsertNewParserToList(ParserAndContainer* p_newParser, std::string p_fileEndingToParse);
    // Forwards the freecall to the correct parser.
    void FreeResource(size_t p_parserHandle, GUID p_guid);

	bool ShouldLoadResource(std::string & p_ending, GUID p_guid);



    // Parses filename with guid and file ending and parses with correct parser
	void ParseByEnding(void * p_fileBuffer, const size_t & p_sizeOfBuffer, std::string & p_ending, GUID p_guid);

	//Call this function when we try to allocate memory that we are not allowed to use (IE Full memory and cant get rid of anything)
	void DumpAllParserData();
	int GetMemoryUsage() { return m_memoryUsage; }
	void AddMemoryUsage(int p_memoryToAdd);
private:
    static ParserAndContainerManager* m_singleton;
    std::unordered_map<std::string, std::vector<ParserAndContainer*>> m_fileEndingToParser;
    std::unordered_map<size_t, ParserAndContainer*>m_prioHandlesToParser;
    size_t m_prioHandleIncrementer;
	int m_memoryUsage;
};

