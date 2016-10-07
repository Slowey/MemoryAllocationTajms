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
   Creates a window with the parameters specified*/
   void CreateWindow(WindowParams p_parameters);

private:
   static Graphics* m_singleton;
   Graphics();
   ~Graphics();
   
};

