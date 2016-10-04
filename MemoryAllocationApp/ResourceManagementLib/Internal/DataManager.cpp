#include "DataManager.h"

DataManager* DataManager::m_singleton = nullptr;

DataManager::DataManager()
{
	m_nextPlaceInTheMap = 0;
}


DataManager::~DataManager()
{
}
void DataManager::Startup()
{
	if (m_singleton != nullptr)
	{
		return;
	}
	m_singleton = new DataManager();
}
void DataManager::FreeResource(std::string p_resource, const size_t & p_size)
{
	//Leta mapp Hitta resource ta bort från mappen (fria upp minne här?)
}
void DataManager::AddResource(std::string p_resourceLocation, void* p_data)
{
	m_resourceStringToVoidPtrMap.insert(std::pair<std::string, void*>(p_resourceLocation, p_data));
	++m_nextPlaceInTheMap;
}
void DataManager::RemoveResource(std::string p_resourceLocation)
{
	m_resourceStringToVoidPtrMap.erase(p_resourceLocation);
}
DataManager * DataManager::Get()
{
	return m_singleton;
}
