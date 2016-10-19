#pragma once
#include <ParserAndContainer.h>
#include <map>
#include <mutex>
struct ParsedObj
{
    unsigned int graphicResourceID;
	size_t size;
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
    void ParseAndSaveParsedData(void* p_dataStart, const size_t &p_size, const GUID &p_guid) override;
    // Returns the parsed data on the GUID
    ParsedObj** GetResource(const GUID& p_guid);

    bool ResourceExist(const GUID & p_guid) override;

	void DumpMemoryData();


private:
    // Acctually deletes the data
    void FreeResource(const GUID &p_guid) override;

    ParsedObj* ParseDataAndSendToGraphic(void* p_dataStart);

    static ObjManager* m_singleton;
    std::map<GUID, ParsedObj*> m_objResources;
    ParsedObj* m_dummyMesh;

    std::shared_ptr<std::mutex> m_mutexLockResourceMap;
};

