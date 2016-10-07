#include "Graphics.h"
#include "Internal\SDLManager.h"

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
    SDLManager::Get()->Startup();
    
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::CreateWindow(WindowParams p_parameters)
{
    SDLManager::Get()->CreateWindow(p_parameters);

}

void Graphics::Update()
{
    SDLManager::Get()->Update();
}
