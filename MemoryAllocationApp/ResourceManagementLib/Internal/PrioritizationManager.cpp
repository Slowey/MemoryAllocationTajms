#include "PrioritizationManager.h"
#include "../LRUPriority.h"

PrioritizationManager* PrioritizationManager::m_singleton = nullptr;

PrioritizationManager::PrioritizationManager(PrioritizationAlgorithm p_algo)
{
	if (p_algo == PrioritizationAlgorithm::LRU)
	{
		m_prioritization = new LRUPriority(m_parserList);
	}
	else if (p_algo == PrioritizationAlgorithm::FIFO)
	{

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

void PrioritizationManager::UpdatePriority(GUID p_id, int & o_parserHandle)
{
	m_prioritization->UpdateMap(p_id, o_parserHandle);
}
