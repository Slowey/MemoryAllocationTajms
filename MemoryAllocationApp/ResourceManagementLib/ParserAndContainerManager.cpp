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

