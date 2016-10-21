#include "WavManager.h"

WavManager* WavManager::m_singleton = nullptr;

WavManager::WavManager(): ParserAndContainer("wav")
{
}


WavManager::~WavManager()
{
}

void WavManager::Initialize()
{
    if (m_singleton != nullptr)
    {
        // already initialized
        throw 1337;
    }
    m_singleton = new WavManager();
}

WavManager & WavManager::Get()
{
    if (m_singleton == nullptr)
    {
        // Not yet initialized
        throw 1337;
    }
    return *m_singleton;
}

bool WavManager::ResourceExist(const GUID & p_guid)
{
    return true; // TODO fix :D
}

void WavManager::ParseAndSaveParsedData(void* p_dataStart, const size_t &p_size, const GUID &p_guid)
{
    // see if we already have the resource
    if (m_wavResources.count(p_guid) != 0)
    {
        // we already have the resource!
        return;
    }

    ParsedWav newParsedData;
    newParsedData.startOfMemory = p_dataStart;
    newParsedData.size = p_size;
    m_wavResources[p_guid] = newParsedData;    
}

void WavManager::FreeResource(const GUID &p_guid)
{
}

void WavManager::DumpMemoryData()
{
}

void WavManager::LoadResource(const GUID & p_guid, const std::string & p_file)
{
    //nothing
}
