#include "Graphics.h"
#include <SDL\SDL.h>
Graphics* Graphics::m_singleton = nullptr;

Graphics * Graphics::Get()
{
   if (m_singleton == nullptr)
      m_singleton = new Graphics();
   return nullptr;
}

Graphics::Graphics()
{
   int derp;
   char* derp1;

   SDL_Window* window;

   SDL_Init(SDL_INIT_VIDEO);

   window = SDL_CreateWindow("window", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
   SDL_Delay(3000);

   SDL_DestroyWindow(window);


}


Graphics::~Graphics()
{
}
