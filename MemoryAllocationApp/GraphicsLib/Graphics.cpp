#include "Graphics.h"
#include "Internal\SDLManager.h"
#include <SDL\SDL.h>
#include <GL2\glew.h>

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
    SDL_Window* window;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
        p_parameters.windowName,
        p_parameters.winPosX, 
        p_parameters.winPosY, 
        p_parameters.winSizeX,
        p_parameters.winSizeY,
        SDL_WINDOW_OPENGL);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    GLenum status = glewInit();
    if (status != GLEW_OK)
        int derp = 5; // Just for debug purpose

    // This has to be done somewhere
    // SDL_DestroyWindow(window);

}
