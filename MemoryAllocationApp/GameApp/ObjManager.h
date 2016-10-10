#pragma once
#include <ParserAndContainer.h>
#include <unordered_map>
struct ParsedObj
{
    unsigned int graphicResourceID;
};

class ObjManager: public ParserAndContainer
{
public:
    ObjManager();
    ~ObjManager();

    // Initialize singleton
    static void Initialize();
    // Get singleton
    static ObjManager& Get();
    // Parses the wav format and saves it to a container mapping between GUID and ... TODO take GUID as input
    void ParseAndSaveParsedData(void* p_dataStart, size_t p_size, GUID p_guid) override;
    // Returns the parsed data on the GUID
    ParsedObj GetResource(const GUID& p_guid);
private:
    static ObjManager* m_singleton;
    std::unordered_map<GUID, ParsedObj> m_objResources;
};

