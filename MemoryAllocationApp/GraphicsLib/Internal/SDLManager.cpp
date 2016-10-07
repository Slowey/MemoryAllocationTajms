// This class
#include "SDLManager.h"

// Third party
#include <SDL\SDL.h>
#include <GL2\glew.h>

// Own stuff
#include "../WindowParams.h"

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

void SDLManager::CreateWindow(WindowParams p_parameters)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // Not sure if these are necessary
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(
        p_parameters.windowName,
        p_parameters.winPosX,
        p_parameters.winPosY,
        p_parameters.winSizeX,
        p_parameters.winSizeY,
        SDL_WINDOW_OPENGL);

    m_glContext = SDL_GL_CreateContext(m_window);
    GLenum status = glewInit();
    glEnable(GL_DEPTH_TEST);
    if (status != GLEW_OK)
        int derp = 5; // Just for debug purpose. Should be done properly somewhere

}

void SDLManager::Update()
{
    // Swap backbuffer
    SDL_GL_SwapWindow(m_window);
    // Update input (TODO)
}


SDLManager * SDLManager::Get()
{
    // TODO make better handling if startup not called
    if(m_singleton != nullptr)
        return m_singleton;
    return nullptr;
}

