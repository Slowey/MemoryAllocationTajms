#pragma once
#include "ParserAndContainer.h"
#include <unordered_map>
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
    void ParseAndSaveParsedData(void* p_dataStart, size_t p_size) override;

private:
    static WavManager* m_singleton;
};

