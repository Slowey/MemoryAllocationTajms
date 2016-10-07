#pragma once

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

private:
    static SDLManager* m_singleton;
    SDLManager();
    ~SDLManager();

};