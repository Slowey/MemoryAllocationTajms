#include "PrioritizationManager.h"
#include "../LRUPriority.h"
#include "../FIFOPriority.h"
#include "../ParserAndContainerManager.h"
#include "ExplicitPriority.h"
#include "LFUPriority.h"

PrioritizationManager* PrioritizationManager::m_singleton = nullptr;

PrioritizationManager::PrioritizationManager(PrioritizationAlgorithm p_algo)
{
	if (p_algo == PrioritizationAlgorithm::LRU)
	{
		m_prioritization = new LRUPriority();
	}
	else if (p_algo == PrioritizationAlgorithm::FIFO)
	{
        m_prioritization = new FIFOPriority();
	}
    else if (p_algo == PrioritizationAlgorithm::EXPLICIT)
    {
        m_prioritization = new ExplicitPriority();
    }
    else if (p_algo == PrioritizationAlgorithm::LFU)
    {
        m_prioritization = new LFUPriority();
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

bool PrioritizationManager::FindAndForwardRemovableResource()
{
    ParserUID t_parserUID = m_prioritization->GetRemovableResource();
    if (t_parserUID.guid != ERROR_GUID)
    {
           //Send to parserandcontainer
		ParserAndContainerManager::Get().FreeResource(t_parserUID.parserHandle, t_parserUID.guid);
	}
    else 
    {
        //We are at capacity
        return false;
    }
    return true;
}

void PrioritizationManager::RemoveFromRemovableQueue(GUID p_id, size_t p_parserHandle)
{
	m_prioritization->RemoveFromRemovableQueue(p_id, p_parserHandle);
}

void PrioritizationManager::AddToRemovableQueue(GUID p_id, size_t p_parserHandle)
{
	m_prioritization->AddToRemovableQueue(p_id, p_parserHandle);
}
