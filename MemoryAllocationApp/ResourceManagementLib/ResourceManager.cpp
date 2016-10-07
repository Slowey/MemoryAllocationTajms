#include "ResourceManager.h"
#include "Internal/DataManager.h"
#include <MemoryManager.h>
#include <PoolAllocator.h>
#pragma comment (lib, "MemLib.lib")

ResourceManager* ResourceManager::m_singleton = nullptr;

ResourceManager::ResourceManager()
{
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
void ResourceManager::ReferencePing()
{
	
}
void ResourceManager::FreeResource(std::string p_resource, const size_t& p_size)
{
	//Skicka vidare till Datamanager
	// Ska minnet frias upp här eller datamanager eller någon annan stans?
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

