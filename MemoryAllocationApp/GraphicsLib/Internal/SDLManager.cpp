// This class
#include "SDLManager.h"

// Third party
#include <SDL\SDL.h>
#include <GL2\glew.h>

// Own stuff
#include "../WindowParams.h"

SDLManager* SDLManager::m_singleton = nullptr;

bool SDLManager::KeysDown(int p_keys)
{
   int result = m_keysPressed & p_keys;
   return result == p_keys;
}

void SDLManager::GetMouseMovement(int & o_x, int & o_y)
{
   o_x = m_deltaX;
   o_y = m_deltaY;
}

void SDLManager::SetLoadContext(bool p_active)
{
   SDL_GL_MakeCurrent(m_window, p_active ? m_loadContext : m_glContext);
}

SDLManager::SDLManager()
{
}

SDLManager::~SDLManager()
{
}

void SDLManager::UpdateInput()
{
   SDL_Event t_event;
   SDL_PumpEvents();
   const Uint8* t_keyState = SDL_GetKeyboardState(NULL);
   m_keysPressed = 0;

   if (t_keyState[SDL_SCANCODE_W])
   {
      m_keysPressed |= (int)InputKey::W;
   }
   if (t_keyState[SDL_SCANCODE_S])
   {
      m_keysPressed |= (int)InputKey::S;
   }
   if (t_keyState[SDL_SCANCODE_A])
   {
      m_keysPressed |= (int)InputKey::A;
   }
   if (t_keyState[SDL_SCANCODE_D])
   {
      m_keysPressed |= (int)InputKey::D;
   }
   if (t_keyState[SDL_SCANCODE_SPACE])
   {
      m_keysPressed |= (int)InputKey::Up;
   }
   if (t_keyState[SDL_SCANCODE_C])
   {
      m_keysPressed |= (int)InputKey::Down;
   }

}

void SDLManager::UpdateMouseInput()
{
   m_deltaX = 0;
   m_deltaY = 0;
   SDL_Event t_event;
   //m_deltaX = 10;
   while (SDL_PollEvent(&t_event))
   {
      if (t_event.type == SDL_MOUSEMOTION)
      {
         int t_windowWidth;
         int t_windowHeight;
         SDL_GetWindowSize(m_window, &t_windowWidth, &t_windowHeight);
         // Ensure we don't change on the warp
         if (t_event.motion.x != t_windowWidth / 2 || t_event.motion.y != t_windowHeight / 2)
         {
            m_deltaX = t_event.motion.xrel;
            m_deltaY = t_event.motion.yrel;
            // Move mouse back to middle of screen
            SDL_WarpMouseInWindow(m_window, t_windowWidth / 2, t_windowHeight / 2);
         }
      }
   }
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
   SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
   

   m_window = SDL_CreateWindow(
      p_parameters.windowName,
      p_parameters.winPosX,
      p_parameters.winPosY,
      p_parameters.winSizeX,
      p_parameters.winSizeY,
      SDL_WINDOW_OPENGL);

   m_glContext = SDL_GL_CreateContext(m_window);
   m_loadContext = SDL_GL_CreateContext(m_window); // Used for loading resources
   SDL_GL_MakeCurrent(m_window, m_glContext);
   // Make render context main
   GLenum status = glewInit();
   glEnable(GL_DEPTH_TEST);
   if (status != GLEW_OK)
      int derp = 5; // Just for debug purpose. Should be done properly somewhere

   // Hide cursor. Probable shouldn't be hardcoded
   SDL_ShowCursor(SDL_DISABLE);
}

void SDLManager::Update()
{
   // Swap backbuffer
   SDL_GL_SwapWindow(m_window);
   UpdateInput();
   UpdateMouseInput();
}


SDLManager * SDLManager::Get()
{
   // TODO make better handling if startup not called
   if (m_singleton != nullptr)
      return m_singleton;
   return nullptr;
}

