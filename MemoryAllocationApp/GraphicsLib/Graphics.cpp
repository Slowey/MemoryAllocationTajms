#include "Graphics.h"
#include <SDL\SDL.h>
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
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        p_parameters.windowName,
        p_parameters.winPosX, 
        p_parameters.winPosY, 
        p_parameters.winSizeX,
        p_parameters.winSizeY,
        SDL_WINDOW_OPENGL);
    // This has to be done somewhere
    // SDL_DestroyWindow(window);

}
