#pragma once
#include <string>
#include <map>
#include "EnumsAndDefines.h"
class ParserAndContainerManager;
class ParserAndContainer
{
public:
    // The file ending this parser wants to parse, should be without the '.'. for example "png"
    ParserAndContainer(std::string p_fileEndingToParse);
    ~ParserAndContainer();

    // Dont delete the raw data, it might be used later!!
    virtual void ParseAndSaveParsedData(void* p_dataStart, const size_t &p_size, const GUID &p_guid) = 0;
    virtual bool ResourceExist(const GUID &p_guid) = 0;
    // Should be called when a object is done using a resource. Every gotten resource needs to be released otherwise the resource manager wont be able to unload it from memory
    void ReleaseResource(const GUID &p_guid);
    void SetPriorityHandle(size_t p_priorityHandle) { m_priorityHandle = p_priorityHandle; };
	virtual void DumpMemoryData() = 0;
    virtual void LoadResource(const GUID &p_guid, const std::string &p_file) = 0;
protected:
    /**
    Should be called every time someone requests a resource.
    This is to ensure the resource manager doesnt remove a resource that is still referenced by the game
    */
    void ResourceRequested(const GUID& p_guid);
	void AddMemoryUsage(int p_memoryUsageToAdd);
    /**
    Releases the resource, removing the data.
    Is called when the prioritization manager have deemed the resources time in memory is up
    */
    virtual void FreeResource(const GUID &p_guid) = 0;
    
    const std::string m_fileEnding;
private:
    // need to befriend this class since it needs access right to FreeResource
    friend class ParserAndContainerManager;

    size_t m_priorityHandle;
    std::map<GUID, size_t> m_activeReferencesToResource;
};

