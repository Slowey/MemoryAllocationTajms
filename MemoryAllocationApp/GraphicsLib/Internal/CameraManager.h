#pragma once
// Third Party
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <GL2\glew.h>

// Standard libraries
#include <vector>

using namespace glm;
/**
Internal singleton to store and update all forms of
camera related stuff. This will directly handle inputs
from the SDL manager. Yup, real clever*/
class CameraManager
{
public:
   static CameraManager* Get();
   static void Startup();
   //Camera* m_camera;

private:
   static CameraManager* m_singleton;
   CameraManager();
   ~CameraManager();
   
};

/**
Struct used internally by the camera manager*/
struct Camera
{
   Camera(vec3 p_pos, vec3 p_tar, vec3 p_up, mat4x4 p_perspective)
      :position(p_pos), target(p_tar), up(p_up), perspective(p_perspective) {}
   vec3 position;
   vec3 target;
   vec3 up;

   mat4x4 perspective;
   mat4x4 world;
};