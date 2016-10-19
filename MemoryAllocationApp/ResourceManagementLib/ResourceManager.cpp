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

ResourceManager::ResourceManager(size_t p_maximumMemoryUsage)
{
    PrioritizationManager::Startup(PrioritizationAlgorithm::LRU);
    m_prioritizationManager = PrioritizationManager::Get();
	MemoryTracker::Startup(p_maximumMemoryUsage);
	m_memoryTracker = MemoryTracker::Get();
    FileLoaderManager::Startup(); // Could save this one as well if we want
    ZZIPLoader* loader = new ZZIPLoader("zip"); // Add shipped loaders 
}


ResourceManager::~ResourceManager()
{
}
void ResourceManager::Startup(size_t p_maximumMemoryUsage)
{
	if (m_singleton != nullptr)
	{
		return;
	}
	m_singleton = new ResourceManager(p_maximumMemoryUsage);
}

void ResourceManager::FreeResource(GUID p_guid)
{
	//Skicka vidare till parser and container OUTDATED
}
void ResourceManager::FreeResource()
{
    m_prioritizationManager->FindAndForwardRemovableResource();
    //SKicka guidet till prioritization för removal.
}

ResourceManager * ResourceManager::Get()
{
	return m_singleton;
}

void ResourceManager::LoadChunk(const std::string & p_fileName)
{
    FileLoaderManager::Get()->LoadChunk(p_fileName);
}


//void ResourceManager::LoadChunk(const std::string & p_fileName, const std::string & p_subDirectory)
//{
//    FileLoaderManager::Get()->LoadChunk(p_fileName, p_subDirectory);
//}

