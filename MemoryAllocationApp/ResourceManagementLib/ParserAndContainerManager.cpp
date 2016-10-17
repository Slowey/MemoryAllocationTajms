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

void ParserAndContainerManager::ParseByEnding(void * p_fileBuffer, const size_t &p_sizeOfBuffer, char * p_fileName)
{
    std::string t_fileNameString(p_fileName);
    size_t t_lastDot = t_fileNameString.find_last_of(".");

    // No ending
    if (t_lastDot == std::string::npos)
        return;

    // Find start of name
    size_t t_beginning = t_fileNameString.find_last_of("/");
    if (t_beginning == std::string::npos)
        t_beginning = -1;

    // Increment because we dont want the slash in the name
    t_beginning++;
    std::string t_ending = t_fileNameString.substr(t_lastDot + 1);
    std::string t_name = t_fileNameString.substr(t_beginning, (t_lastDot - t_beginning));

    // We have decided to use split sign in ID, ask Techis & Jaws
    size_t t_idSplit = t_name.find_last_of("_");
    if (t_idSplit == std::string::npos)
        return;

    GUID t_guid = GUID(t_name);

    // Find all parsers and parse for ending
    auto m_pair = m_fileEndingToParser.find(t_ending);
    if (m_pair == m_fileEndingToParser.end())
        return;

    auto m_parsers = m_pair->second;
    size_t t_numParsers = m_parsers.size();
    for (size_t i = 0; i < t_numParsers; i++)
    {
        if (!m_parsers[i]->ResourceExist(t_guid))
        {
            m_parsers[i]->ParseAndSaveParsedData(p_fileBuffer, p_sizeOfBuffer, t_guid);
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
