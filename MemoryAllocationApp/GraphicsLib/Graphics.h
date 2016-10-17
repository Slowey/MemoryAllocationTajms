#pragma once
// Third party
#include <glm\glm.hpp>

// Standard library
#include <vector>
#include <unordered_map>

// Our stuff
#include "WindowParams.h"
#include "Vertex.h"

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
   Creates a mesh from provided vertices and returns handle.
   p_async specifies if we want to load asynchronously*/
   unsigned int CreateMesh(std::vector<Vertex>& p_vertices, bool p_async);

   /**
   Loads a texture and returns handle.
   Provide data pointer and file lenth, in bytes*/
   unsigned int LoadTexture(void* p_data, int p_textureByteSize);

   /**
   Loads a texture and returns handle.
   Provide file name.*/
   unsigned int LoadTexture(const char* p_fileName);

   /**
   Draws desired mesh at world position and rotation
   specified in the provided world matrix parameter.
   If the mesh ID does not exist, nothing will happen.*/
   void DrawObject(unsigned int p_meshID, glm::mat4x4 p_worldMatrix, unsigned int p_textureID);

   /**
   Returns the position of the camera. This design is
   really really silly...*/
   glm::vec3 GetCameraPosition();

private:
   static Graphics* m_singleton;
   Graphics();
   ~Graphics();
   
   
   
};

