#include "ResourceManager.h"
#include "Internal/DataManager.h"
#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "Internal/PrioritizationManager.h"
#include "EnumsAndDefines.h"
#include "Internal/FileLoaderManager.h"

// Shipped loaders
#include "Internal/ZZIPLoader.h"

#pragma comment (lib, "MemLib.lib")

ResourceManager* ResourceManager::m_singleton = nullptr;

ResourceManager::ResourceManager()
{
    PrioritizationManager::Startup(PrioritizationAlgorithm::LRU);
    m_prioritizationManager = PrioritizationManager::Get();
    FileLoaderManager::Startup(); // Could save this one as well if we want
    ZZIPLoader* loader = new ZZIPLoader("zip"); // Add shipped loaders 
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
    m_prioritizationManager->GetRemovableResource();
    //SKicka guidet till parser and container för removal.
}

ResourceManager * ResourceManager::Get()
{
	return m_singleton;
}


void ResourceManager::LoadChunk(std::string &p_fileName)
{
    FileLoaderManager::Get()->LoadChunk(p_fileName);
}

