#include "LRUPriority.h"


LRUPriority* LRUPriority::m_singleton = nullptr;

LRUPriority * LRUPriority::Get()
{
	return m_singleton;
}

LRUPriority::LRUPriority()
{
}


LRUPriority::~LRUPriority()
{
}

void LRUPriority::Startup()
{
	if (m_singleton != nullptr)
	{
		return;
	}
	m_singleton = (LRUPriority*)malloc(sizeof(LRUPriority));
	new (m_singleton) LRUPriority();
}

void LRUPriority::UpdateMap(std::string)
{
}

void LRUPriority::AddToMap(std::string)
{
}

std::string LRUPriority::PopLeastRecentlyUsed()
{
	size_t t_leastRecentUsedValue = 0;
	std::string t_leastRecentlyUsedGUID = ""; //Ska vara en guid.
	for (auto iterator = m_priorityMap.begin(); iterator != m_priorityMap.end(); iterator++) {

	}


	return std::string();
}
