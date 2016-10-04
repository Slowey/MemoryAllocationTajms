#include "ResourceManager.h"
#include "Internal/DataManager.h"

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
void ResourceManager::FreeResource(std::string p_resource, const size_t& p_size)
{
	//Skicka vidare till Datamanager
	// Ska minnet frias upp här eller datamanager eller någon annan stans?
}

ResourceManager * ResourceManager::Get()
{
	return m_singleton;
}

