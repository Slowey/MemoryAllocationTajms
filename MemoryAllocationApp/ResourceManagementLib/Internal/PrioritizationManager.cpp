#include "PrioritizationManager.h"
#include "../LRUPriority.h"

PrioritizationManager* PrioritizationManager::m_singleton = nullptr;

PrioritizationManager::PrioritizationManager(PrioritizationAlgorithm p_algo)
{
	if (p_algo == PrioritizationAlgorithm::LRU)
	{
		LRUPriority::Startup();
	}
}


PrioritizationManager::~PrioritizationManager()
{
}
PrioritizationManager * PrioritizationManager::Get()
{
	return m_singleton;
}
void PrioritizationManager::Startup(PrioritizationAlgorithm p_algo)
{
	if (m_singleton != nullptr)
	{
		return;
	}
	m_singleton = (PrioritizationManager*)malloc(sizeof(PrioritizationManager));
	new (m_singleton) PrioritizationManager(p_algo);
}
