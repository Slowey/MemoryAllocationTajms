#include "SDLManager.h"

SDLManager* SDLManager::m_singleton = nullptr;

SDLManager::SDLManager()
{
}

SDLManager::~SDLManager()
{
}

void SDLManager::Startup()
{
    m_singleton = new SDLManager();
}


SDLManager * SDLManager::Get()
{
    // TODO make better handling if startup not called
    if(m_singleton != nullptr)
        return m_singleton;
    return nullptr;
}

