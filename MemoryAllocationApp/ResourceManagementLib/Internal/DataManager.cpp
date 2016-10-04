#include "DataManager.h"

DataManager* DataManager::m_singleton = nullptr;

DataManager::DataManager()
{
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
	//Leta mapp Hitta resource ta bort fr�n mappen (fria upp minne h�r?)
}
DataManager * DataManager::Get()
{
	return m_singleton;
}
