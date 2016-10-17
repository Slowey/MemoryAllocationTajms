#include "MemoryTracker.h"
#include "ParserAndContainerManager.h"

MemoryTracker* MemoryTracker::m_singleton = nullptr;

MemoryTracker* MemoryTracker::Get()
{
	return m_singleton;
}

void MemoryTracker::Startup(size_t p_maximumMemory)
{
	if (m_singleton == nullptr)
	{
		m_singleton = new MemoryTracker(p_maximumMemory);
	}
}
MemoryTracker::MemoryTracker(size_t p_maximumMemory)
{
}

MemoryTracker::~MemoryTracker()
{
}

bool MemoryTracker::CheckIfMemoryAvailable(size_t p_desiredMemory)
{
	size_t t_currentMemoryUsage = ParserAndContainerManager::Get().GetMemoryUsage();
	if (t_currentMemoryUsage + p_desiredMemory < m_maximumMemory)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
