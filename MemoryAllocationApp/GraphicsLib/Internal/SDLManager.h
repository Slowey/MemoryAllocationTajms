#pragma once
// Third party
#include <SDL\SDL.h>

// Own stuff
#include "../WindowParams.h"

/**
Singleton to handle all SDL thingies, such as
the window and input. Meant to only be accessed
internally by the graphics lib*/
class SDLManager
{
public:
    /**
    Get sdl singleton pointer.
    Make sure startup has been called first!*/
    static SDLManager* Get();

    /**
    Creates the sdl manager Call this before
    using the singleton in any way.*/
    static void Startup();

    /**
    Creates a window with the parameters specified.
    This also initializes openGL (yes, that's how we're doing it)*/
    void CreateWindow(WindowParams p_parameters);

    /**
    Swaps backbuffer and updates all inputs.*/
    void Update();

private:
    static SDLManager* m_singleton;
    SDLManager();
    ~SDLManager();
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};