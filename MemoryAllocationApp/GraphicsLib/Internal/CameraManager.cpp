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
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
