// This class
#include "CameraManager.h"

// Our stuff
#include "SDLManager.h"

// Debug stuff
#include <iostream>
using namespace std;
// end debug
CameraManager* CameraManager::m_singleton = nullptr;

CameraManager * CameraManager::Get()
{
   if (m_singleton != nullptr)
      return m_singleton;
   return nullptr;
}

void CameraManager::Startup()
{
   m_singleton = new CameraManager();
}

CameraManager::CameraManager()
{
   // Create camera
   mat4x4 t_perspective = perspective(radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
   m_camera = new Camera(vec3(0, 0, -1), vec3(0, 0, 1), vec3(0, 1, 0), t_perspective);

   // Set some variables
   m_movementSpeed = 0.001f;
   m_turnSpeed = 0.0001f;
}

CameraManager::~CameraManager()
{
}


void CameraManager::Update()
{
   /// Translation
   vec3 t_movement;
   // Forward and back
   if (SDLManager::Get()->KeysDown((int)InputKey::W))
      t_movement += m_camera->target * m_movementSpeed;
   if (SDLManager::Get()->KeysDown((int)InputKey::S))
      t_movement -= m_camera->target * m_movementSpeed;

   // Right and left
   // Compute right vector
   vec3 t_right = cross(m_camera->up, m_camera->target);
   if (SDLManager::Get()->KeysDown((int)InputKey::D))
      t_movement -= t_right * m_movementSpeed;
   if (SDLManager::Get()->KeysDown((int)InputKey::A))
      t_movement += t_right * m_movementSpeed;

   // Up and down
   if (SDLManager::Get()->KeysDown((int)InputKey::Up))
      t_movement += m_camera->up * m_movementSpeed;
   if (SDLManager::Get()->KeysDown((int)InputKey::Down))
      t_movement -= m_camera->up * m_movementSpeed;

   m_camera->position += t_movement;

   /// Rotation
   // Get deltas and convert to floats
   int t_dx;
   int t_dy;
   SDLManager::Get()->GetMouseMovement(t_dx, t_dy);
   cout << t_dx << "  " << t_dy << endl;
   /* Might actually be an idea to normalize the deltas
   since y moves slower than x due to x being more pixels.*/
   float t_rotationX = (float)t_dx * m_turnSpeed;
   float t_rotationY = (float)t_dy * m_turnSpeed;
   // Get vec4s so we can make algebra magic
   vec4 t_up4 = vec4(normalize(m_camera->up), 0);
   vec4 t_target4 = vec4(normalize(m_camera->target), 0);
   vec4 t_right4 = vec4(cross(m_camera->target, m_camera->up), 0); // Might be wrong order of cross
   //vec4 t_right4 = vec4(cross(m_camera->up, m_camera->target), 0); // Might be wrong order of cross

   // Rotate around right vector
   mat4x4 t_rightRotateMat = rotate(-t_rotationY, vec3(t_right4));
   t_target4 = t_rightRotateMat * t_target4;
   //t_up4 = t_rightRotateMat * t_up4;

   // Rotate around up vector
   //mat4x4 t_upRotateMat = rotate(t_rotationX, vec3(t_up4));
   mat4x4 t_upRotateMat = rotate(-t_rotationX, vec3(0,1,0));
   t_target4 = t_upRotateMat * t_target4;

   // Store results
   m_camera->target = vec3(t_target4);
   m_camera->up = vec3(t_up4);

   // Create world matrix
   m_camera->world = lookAt(m_camera->position, m_camera->position + m_camera->target, m_camera->up);

}

mat4x4 CameraManager::GetCameraMatrix()
{
   return m_camera->perspective * m_camera->world;
}
