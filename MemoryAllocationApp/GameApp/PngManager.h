#pragma once
#include <ParserAndContainer.h>
#include <map>
#include <mutex>

struct ParsedPng
{
    unsigned int graphicResourceID;
};

class PngManager: public ParserAndContainer
{
public:
    PngManager();
    ~PngManager();
    // Initialize singleton
    static void Initialize();
    // Get singleton
    static PngManager& Get();
    // Parses the png format and saves it to a container mapping between GUID and ... TODO take GUID as input
    void ParseAndSaveParsedData(void* p_dataStart, const size_t &p_size, const GUID &p_guid) override;
    // Returns the parsed data on the GUID
    ParsedPng** GetResource(const GUID& p_guid);

    bool ResourceExist(const GUID & p_guid) override;

    void DumpMemoryData();

    void LoadResource(const GUID &p_guid, const std::string &p_file) override;
private:
    // Acctually deletes the data
    void FreeResource(const GUID &p_guid) override;

    static PngManager* m_singleton;

    std::map<GUID, ParsedPng*> m_pngResources;
    ParsedPng* m_dummyTexture;

    std::shared_ptr<std::mutex> m_mutexLockResourceMap;
};

