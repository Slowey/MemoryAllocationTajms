#include "ParserAndContainer.h"
#include "ParserAndContainerManager.h"
#include "Internal/PrioritizationManager.h"


ParserAndContainer::ParserAndContainer(std::string p_fileEndingToParse)
{
    ParserAndContainerManager::Get().InsertNewParserToList(this, p_fileEndingToParse);
}


ParserAndContainer::~ParserAndContainer()
{
}

void ParserAndContainer::ReleaseResource(const GUID & p_guid)
{
    if (m_activeReferencesToResource.count(p_guid) != 0)
    {
        // mutex::lock()
        m_activeReferencesToResource.at(p_guid)--;
        // mutex::unlock()
        if (m_activeReferencesToResource.at(p_guid) == 0)
        {
            PrioritizationManager::Get()->AddToRemovableQueue(p_guid, m_priorityHandle);
        }
    }
    else
    {
        // Shouldnt get here
        throw 1337;
    }
}
void ParserAndContainer::SetMemoryUsage(int p_memoryUsageToAdd) {
	ParserAndContainerManager::Get().SetMemoryUsage(p_memoryUsageToAdd);
}

void ParserAndContainer::ResourceRequested(const GUID& p_guid)
{
    if (m_activeReferencesToResource.count(p_guid) != 0)
    {
        if (m_activeReferencesToResource.at(p_guid) == 0)
        {
            PrioritizationManager::Get()->RemoveFromRemovableQueue(p_guid, m_priorityHandle);
        }
        // mutex::lock()
        m_activeReferencesToResource.at(p_guid)++;
        // mutex::unlock()
    }
    else
    {
        // First time the resource is gotten, 1 referense.
        // mutex::lock()
        m_activeReferencesToResource[p_guid] = 1;
        // mutex::unlock()
    }
}
