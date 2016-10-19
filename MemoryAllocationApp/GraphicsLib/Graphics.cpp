#include "Graphics.h"
#include "Internal\SDLManager.h"
#include "Internal\RenderManager.h"
#include "Internal\CameraManager.h"

Graphics* Graphics::m_singleton = nullptr;

Graphics * Graphics::Get()
{
   //if (m_singleton == nullptr)
   // Implement some sort of warning
   return m_singleton;
}

void Graphics::Startup()
{
    m_singleton = new Graphics();
    
}

void Graphics::DrawObject(unsigned int p_meshID, glm::mat4x4 p_worldMatrix, unsigned int p_textureID)
{
   RenderManager::Get()->AddMatrixToMeshDrawList(p_meshID, p_worldMatrix, p_textureID);
}

glm::vec3 Graphics::GetCameraPosition()
{
   return CameraManager::Get()->GetCameraPosition();
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

void Graphics::CreateWindow(WindowParams p_parameters)
{
    // This order is VERY important. Don't mess with it
    SDLManager::Startup();
    SDLManager::Get()->CreateWindow(p_parameters);
    RenderManager::Startup();
    CameraManager::Startup();
}

void Graphics::Update()
{
    SDLManager::Get()->Update();
    CameraManager::Get()->Update();
    RenderManager::Get()->Render();
}

unsigned int Graphics::CreateMesh(std::vector<glm::vec3>& p_positions)
{
   return RenderManager::Get()->CreateMesh(p_positions);
}

unsigned int Graphics::CreateMesh(std::vector<Vertex>& p_vertices, bool p_async)
{
   return RenderManager::Get()->CreateMesh(p_vertices, p_async);
}

unsigned int Graphics::LoadTexture(void * p_data, int p_textureByteSize, bool p_async)
{
   return RenderManager::Get()->CreateTexture(p_data, p_textureByteSize, p_async);
}

unsigned int Graphics::LoadTexture(const char * p_fileName)
{
   return RenderManager::Get()->CreateTexture(p_fileName);
}
