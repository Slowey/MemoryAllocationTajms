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

void WavManager::ParseAndSaveParsedData(void* p_dataStart, size_t p_size, GUID p_guid)
{
    ParsedWav newParsedData;
    newParsedData.startOfMemory = p_dataStart;
    newParsedData.size = p_size;
    m_wavResources[p_guid] = newParsedData;    
}
