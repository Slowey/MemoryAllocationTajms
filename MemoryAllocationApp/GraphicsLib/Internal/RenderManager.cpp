// This class
#include "RenderManager.h"

RenderManager* RenderManager::m_singleton = nullptr;

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}


RenderManager * RenderManager::Get()
{
    // Todo: safer handling when startup not called
    if (m_singleton != nullptr)
        return m_singleton;
    return nullptr;
}

void RenderManager::Startup()
{
    m_singleton = new RenderManager();
}

