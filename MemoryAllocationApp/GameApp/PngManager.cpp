#include "PngManager.h"
#include <ParserAndContainerManager.h>
#include <Graphics.h>
#include "Global.h"
#include <MemoryTracker.h>
#include <ResourceManager.h>

PngManager* PngManager::m_singleton = nullptr;

PngManager::PngManager(): ParserAndContainer("png")
{
    m_mutexLockResourceMap = std::make_shared<std::mutex>();

    m_dummyTexture = new ParsedPng();
    m_dummyTexture->graphicResourceID = 1;
}


PngManager::~PngManager()
{
}

void PngManager::Initialize()
{
    if (m_singleton != nullptr)
    {
        throw 1337;
    }
    m_singleton = new PngManager();
}

PngManager & PngManager::Get()
{
    if (m_singleton == nullptr)
    {
        throw 1337;
    }
    return *m_singleton;
}

void PngManager::ParseAndSaveParsedData(void * p_dataStart, const size_t & p_size, const GUID & p_guid)
{
    // see if we already have the resource and its not the dummy
    if (ResourceExist(p_guid))
    {
        // we already have the resource!
        return;
    }
    ParsedPng* newResource = new ParsedPng;
    // Might need to say if we are main thread or not...
    newResource->graphicResourceID = Graphics::Get()->LoadTexture(p_dataStart, p_size, !IsMainThread());

    newResource->size = p_size;
    if (!MemoryTracker::Get()->CheckIfMemoryAvailable(newResource->size))
    {
       //We cant allocate this. Cos memory is full. Time to crash!
       throw 1337;
    }

    m_mutexLockResourceMap->lock();
    m_pngResources[p_guid] = newResource;
    m_mutexLockResourceMap->unlock();
}

void PngManager::DumpMemoryData()
{
    FILE * pFile;
    fopen_s(&pFile, "PNGParserDataDump", "w");
    for (auto iterator = m_pngResources.begin(); iterator != m_pngResources.end(); iterator++)
    {
		if (iterator->second != m_dummyTexture)
		{
			fprintf(pFile, "%d, %d", iterator->first.val[0], iterator->first.val[1]);
		}
    }
    // Glöm inte att spara ner vilken resurs som skulle bli inladdad när overflowen occurade.
	fclose(pFile);
}

void PngManager::LoadResource(const GUID & p_guid, const std::string & p_file)
{
    if (m_pngResources.count(p_guid) != 0)
        return;


    bool t_shouldLoad = false;
    // The resource doesn't exist.. :( Return debug shit)
    while (!m_mutexLockResourceMap->try_lock())
    {
        if (m_pngResources.count(p_guid) == 0)
        {
            m_pngResources[p_guid] = m_dummyTexture;
            t_shouldLoad = true;
        }

        m_mutexLockResourceMap->unlock();
        break;
    }

    if (t_shouldLoad)
        ResourceManager::Get()->LoadResource(p_guid, m_fileEnding, p_file);
}

ParsedPng ** PngManager::GetResource(const GUID & p_guid)
{
    if (m_pngResources.count(p_guid) == 0)
    {
        LoadResource(p_guid, ResourceManager::Get()->GetSavedPathFromGUID(p_guid));
    }
    return &m_pngResources.at(p_guid);
}

bool PngManager::ResourceExist(const GUID & p_guid)
{
    bool r_exists = m_pngResources.count(p_guid) != 0 && m_pngResources.at(p_guid) != m_dummyTexture;
    return r_exists;
}

void PngManager::FreeResource(const GUID & p_guid)
{
    if (ResourceExist(p_guid))
    {
        // should call graphic manager to remove the gpu resource to...
        AddMemoryUsage(-1 * m_pngResources.at(p_guid)->size);
        delete m_pngResources.at(p_guid);
        m_pngResources.erase(p_guid);
    }
}
