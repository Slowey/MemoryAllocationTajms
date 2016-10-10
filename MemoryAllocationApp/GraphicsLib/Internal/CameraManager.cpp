// This class
#include "CameraManager.h"

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
   mat4x4 t_perspective = perspectiveFov(90, 1920, 1080, 1, 1000);
   //CameraManager::Get()->m_camera = new Camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0), t_perspective);
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
