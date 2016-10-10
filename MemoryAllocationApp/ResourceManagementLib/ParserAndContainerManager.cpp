#include "ParserAndContainerManager.h"
#include "ParserAndContainer.h"

ParserAndContainerManager* ParserAndContainerManager::m_singleton = nullptr;

ParserAndContainerManager::ParserAndContainerManager()
{
}


ParserAndContainerManager::~ParserAndContainerManager()
{
}

void ParserAndContainerManager::Initialize()
{
    if (m_singleton != nullptr)
    {
        // already initialized
        throw 1337;
    }
    m_singleton = new ParserAndContainerManager();
}

ParserAndContainerManager & ParserAndContainerManager::Get()
{
    if (m_singleton == nullptr)
    {
        // Not yet initialized
        throw 1337;
    }
    return *m_singleton;
}

void ParserAndContainerManager::InsertNewParserToList(ParserAndContainer* p_newParser, std::string p_fileEndingToParse)
{
    m_fileEndingToParser[p_fileEndingToParse].push_back(p_newParser);
}

void ParserAndContainerManager::ParseByEnding(void * p_fileBuffer, size_t p_sizeOfBuffer, char * p_fileName)
{
    std::string t_fileNameString(p_fileName);
    size_t t_lastDot = t_fileNameString.find_last_of(".");
    std::string t_ending = t_fileNameString.substr(t_lastDot);
    std::string t_name = t_fileNameString.substr(0, t_lastDot);

    int a = 3;
}
