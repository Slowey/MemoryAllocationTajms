#pragma once
// Third party
#include <glm\glm.hpp>

// Standard library
#include <vector>
#include <unordered_map>

// Our stuff
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

   /**
   Loads a mesh into a vertex buffer and returns the ID*/
   unsigned int CreateMesh(std::vector<glm::vec3>& p_positions);

   /**
   Draws desired mesh at world position and rotation
   specified in the provided world matrix parameter.*/
   void DrawObject(unsigned int p_meshID, glm::mat4x4 p_worldMatrix);

private:
   static Graphics* m_singleton;
   Graphics();
   ~Graphics();
   
   std::unordered_map<unsigned int, std::vector<glm::mat4x4>> m_meshDrawLists;
   
};

