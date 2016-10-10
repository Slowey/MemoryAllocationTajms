#pragma once
#include "ParserAndContainer.h"

#include <map>
struct ParsedWav
{
    void* startOfMemory;
    size_t size;
};

class WavManager: public ParserAndContainer
{
public:
    WavManager();
    ~WavManager();

    // Initialize singleton
    static void Initialize();
    // Get singleton
    static WavManager& Get();
    // Parses the wav format and saves it to a container mapping between GUID and ... TODO take GUID as input
    void ParseAndSaveParsedData(void* p_dataStart, size_t p_size, GUID p_guid) override;

    void FreeResource(GUID p_guid) override;
private:
    static WavManager* m_singleton;
    // Contains all the loaded wav resources, parsed and ready to use
    std::map<GUID, ParsedWav> m_wavResources;
};

