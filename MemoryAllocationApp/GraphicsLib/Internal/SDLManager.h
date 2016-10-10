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

    /**
    Returns whether the mask provided is pressed
    down. Build bit mask from enum class InputKey*/
    bool KeysDown(int p_keys);

private:
    static SDLManager* m_singleton;
    SDLManager();
    ~SDLManager();

    void UpdateInput();


    int m_keysPressed;
    
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

};
enum class InputKey
{
   W = 0x01,
   S = 0x02,
   A = 0x04,
   D = 0x08,
   Up = 0x10,
   Down = 0x20,
};
