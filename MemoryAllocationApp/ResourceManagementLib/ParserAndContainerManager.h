#pragma once
class ParserAndContainer;

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

private:
    static ParserAndContainerManager* m_singleton;
    std::unordered_map<std::string, std::vector<ParserAndContainer*>> m_fileEndingToParser;
    std::unordered_map<size_t, ParserAndContainer*>m_prioHandlesToParser;
    size_t m_prioHandleIncrementer;
};

