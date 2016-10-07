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

private:
    static ParserAndContainerManager* m_singleton;
    std::unordered_map<std::string, std::vector<ParserAndContainer*>> m_fileEndingToParser;
};

