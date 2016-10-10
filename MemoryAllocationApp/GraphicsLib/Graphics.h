#pragma once
#include "WindowParams.h"

class Graphics
{
public:
    /**
    Gets an instance of the graphics singleton.
    Make sure startup has been called first!*/
   static Graphics* Get();
   /**
   Creates the graphics manager. Call this before
   using the graphics singleton in any way.*/
   static void Startup();
   /** 
   Creates a window with the parameters specified.
   This also initializes openGL (yes, that's how we're doing it)*/
   void CreateWindow(WindowParams p_parameters);

   /**
   Performs a graphics update with all that it includes*/
   void Update();

private:
   static Graphics* m_singleton;
   Graphics();
   ~Graphics();
   
};

