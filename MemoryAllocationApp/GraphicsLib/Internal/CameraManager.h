#pragma once
// Third Party
#include <glm/glm.hpp>
#include <GL2\glew.h>

// Standard libraries
#include <vector>

/**
Internal singleton to store and update all forms of
camera related stuff. This will directly handle inputs
from the SDL manager. Yup, real clever*/
class CameraManager
{
public:
   static CameraManager* Get();
   static void Startup();

private:
   static CameraManager* m_singleton;
   CameraManager();
   ~CameraManager();
};