#include "MemoryTracker.h"
#include "Internal/PrioritizationManager.h"

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
MemoryTracker::MemoryTracker(size_t p_maximumMemory) : m_maximumMemory(p_maximumMemory), m_usedMemory(0)
{
}

MemoryTracker::~MemoryTracker()
{
}

void MemoryTracker::AddMemoryUsage(int p_memoryToAdd) {
	m_usedMemory += p_memoryToAdd;
}

bool MemoryTracker::CheckIfMemoryAvailable(size_t p_desiredMemory)
{
	// Loop as long as we cant fit the desired memory. If we cannot remove more resources crash!
	while (m_usedMemory + p_desiredMemory > m_maximumMemory)
	{
		if (!PrioritizationManager::Get()->FindAndForwardRemovableResource())
		{
			return false;
		}
	}
	return true;
}
