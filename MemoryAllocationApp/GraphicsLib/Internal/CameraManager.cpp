// This class
#include "CameraManager.h"

// Our stuff
#include "SDLManager.h"

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

void CameraManager::Update()
{
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
      t_movement += t_right * m_movementSpeed;
   if (SDLManager::Get()->KeysDown((int)InputKey::A))
      t_movement -= t_right * m_movementSpeed;

   // Up and down
   if (SDLManager::Get()->KeysDown((int)InputKey::Up))
      t_movement += m_camera->up * m_movementSpeed;
   if (SDLManager::Get()->KeysDown((int)InputKey::Down))
      t_movement -= m_camera->up * m_movementSpeed;

   m_camera->position += t_movement;

   // Create world matrix
   m_camera->world = lookAt(m_camera->position, m_camera->position + m_camera->target, m_camera->up);

}

mat4x4 CameraManager::GetCameraMatrix()
{
   return m_camera->world; // Add perspective?
}

CameraManager::CameraManager()
{
   // Create camera
   mat4x4 t_perspective = perspectiveFov(90, 1920, 1080, 1, 1000);
   m_camera = new Camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0), t_perspective);

   // Set some variables
   m_movementSpeed = 0.01f;
}

CameraManager::~CameraManager()
{
}
