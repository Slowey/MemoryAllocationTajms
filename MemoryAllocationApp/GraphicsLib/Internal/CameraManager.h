#pragma once
// Third Party
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <GL2\glew.h>

// Standard libraries
#include <vector>

using namespace glm;
/**
Struct used internally by the camera manager*/
struct Camera
{
   Camera(vec3 p_pos, vec3 p_tar, vec3 p_up, mat4x4 p_perspective)
      :position(p_pos), target(p_tar), up(p_up), perspective(p_perspective) 
   {
      world = lookAt(p_pos, p_pos + p_tar, p_up);
   }
   vec3 position;
   vec3 target;
   vec3 up;

   mat4x4 perspective;
   mat4x4 world;
};

/**
Internal singleton to store and update all forms of
camera related stuff. This will directly handle inputs
from the SDL manager. Yup, real clever*/
class CameraManager
{
public:
   static CameraManager* Get();
   static void Startup();
   void Update();

   mat4x4 GetCameraMatrix();
   vec3 GetCameraPosition();
   Camera* m_camera;

private:
   static CameraManager* m_singleton;
   CameraManager();
   ~CameraManager();
   float m_movementSpeed;
   float m_turnSpeed;
};

