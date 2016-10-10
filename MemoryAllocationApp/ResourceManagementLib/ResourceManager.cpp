#include "ResourceManager.h"
#include "Internal/DataManager.h"
#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "Internal/PrioritizationManager.h"
#include "EnumsAndDefines.h"
#pragma comment (lib, "MemLib.lib")

ResourceManager* ResourceManager::m_singleton = nullptr;

ResourceManager::ResourceManager()
{
    PrioritizationManager::Startup(PrioritizationAlgorithm::LRU);
    m_prioritizationManager = PrioritizationManager::Get();
}


ResourceManager::~ResourceManager()
{
}
void ResourceManager::Startup()
{
	if (m_singleton != nullptr)
	{
		return;
	}
	m_singleton = new ResourceManager();
}

void ResourceManager::FreeResource(GUID p_guid)
{
	//Skicka vidare till parser and container
}
void ResourceManager::FreeResource()
{
    GUID t_guidOfRemovableResource = m_prioritizationManager->GetRemovableResource();
    //SKicka guidet till parser and container för removal.
}

ResourceManager * ResourceManager::Get()
{
	return m_singleton;
}

#include "Internal/ZZIPLoader.h"
void ResourceManager::LoadChunk(std::string &p_fileName)
{
    ZZIPLoader* loader = new ZZIPLoader("test");

    loader->LoadFile(p_fileName);
}

