#include "ParserAndContainerManager.h"
#include "ParserAndContainer.h"

ParserAndContainerManager* ParserAndContainerManager::m_singleton = nullptr;

ParserAndContainerManager::ParserAndContainerManager()
{
    m_prioHandleIncrementer = 0;
	m_memoryUsage = 0;
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

bool ParserAndContainerManager::ShouldLoadResource(std::string &p_ending, GUID p_guid)
{
	auto m_pair = m_fileEndingToParser.find(p_ending);
    if (m_pair == m_fileEndingToParser.end())
    {
        return false;
    }
	auto m_parsers = m_pair->second;
	size_t t_numParsers = m_parsers.size();
	for (size_t i = 0; i < t_numParsers; i++)
	{
		if (!m_parsers[i]->ResourceExist(p_guid))
		{
			return true;
		}
	}

	return false;
}

void ParserAndContainerManager::ParseByEnding(void * p_fileBuffer, const size_t &p_sizeOfBuffer, std::string &p_ending, GUID p_guid)
{
    
	// Find all parsers and parse for ending
	auto m_pair = m_fileEndingToParser.find(p_ending);
	if (m_pair == m_fileEndingToParser.end())
		return;

    auto m_parsers = m_pair->second;
    size_t t_numParsers = m_parsers.size();
    for (size_t i = 0; i < t_numParsers; i++)
    {
        if (!m_parsers[i]->ResourceExist(p_guid))
        {
            m_parsers[i]->ParseAndSaveParsedData(p_fileBuffer, p_sizeOfBuffer, p_guid);
        }
    }
}

void ParserAndContainerManager::DumpAllParserData()
{
	for (auto iterator = m_prioHandlesToParser.begin(); iterator != m_prioHandlesToParser.end(); iterator++)
	{
		iterator->second->DumpMemoryData();
	}
}

void ParserAndContainerManager::AddMemoryUsage(int p_memoryToAdd)
{
	m_memoryUsage += p_memoryToAdd;
}
