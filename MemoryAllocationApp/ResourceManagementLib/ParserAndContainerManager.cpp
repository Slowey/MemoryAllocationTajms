#include "ParserAndContainerManager.h"
#include "ParserAndContainer.h"

ParserAndContainerManager* ParserAndContainerManager::m_singleton = nullptr;

ParserAndContainerManager::ParserAndContainerManager()
{
    m_prioHandleIncrementer = 0;
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
    p_newParser->SetPriorityHandle(m_prioHandleIncrementer);
    m_prioHandlesToParser[m_prioHandleIncrementer] = p_newParser;
    m_prioHandleIncrementer++;
}

void ParserAndContainerManager::FreeResource(size_t p_parserHandle, GUID p_guid)
{
    m_prioHandlesToParser[p_parserHandle]->FreeResource(p_guid);
}

