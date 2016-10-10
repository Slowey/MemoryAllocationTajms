#include "Graphics.h"
#include "Internal\SDLManager.h"
#include "Internal\RenderManager.h"

Graphics* Graphics::m_singleton = nullptr;

Graphics * Graphics::Get()
{
   //if (m_singleton == nullptr)
   // Implement some sort of warning
   return m_singleton;
}

void Graphics::Startup()
{
    m_singleton = new Graphics();
    
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::CreateWindow(WindowParams p_parameters)
{
    // This order is VERY important. Don't mess with it
    SDLManager::Startup();
    SDLManager::Get()->CreateWindow(p_parameters);
    RenderManager::Startup();
}

void Graphics::Update()
{
    SDLManager::Get()->Update();
    RenderManager::Get()->Render();
}
