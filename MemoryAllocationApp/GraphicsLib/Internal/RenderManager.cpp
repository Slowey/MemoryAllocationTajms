// This class
#include "RenderManager.h"

// Our stuff
#include "CameraManager.h"


// debug
#include <iostream>
#include "SDLManager.h"
using namespace std;

RenderManager* RenderManager::m_singleton = nullptr;

void RenderManager::AddMatrixToMeshDrawList(unsigned int p_meshID, glm::mat4x4 p_worldMatrix)
{
   if (m_meshDrawLists.find(p_meshID) == m_meshDrawLists.end())
   {
      // Mesh didn't exist! We do nothing. This could be changed for debug assistance
      return;
   }
   m_meshDrawLists[p_meshID].push_back(p_worldMatrix);
}

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

GLuint RenderManager::CreateMesh(std::vector<glm::vec3>& p_positions)
{
   GLuint r_positionBuffer;
   glGenBuffers(1, &r_positionBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, r_positionBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * p_positions.size(), &p_positions[0], GL_STATIC_DRAW);
   // Create empty draw list for new mesh
   m_meshDrawLists[r_positionBuffer] = vector<mat4x4>();
   return r_positionBuffer;
}

void RenderManager::DEBUGTriangleCreation()
{
      vector<vec3> t_positions;
      t_positions.push_back(vec3(-0.5, -0.5, 1));
      t_positions.push_back(vec3(0.5, -0.5, 1));
      t_positions.push_back(vec3(0, 0.5, 1));
      GLuint meshVBO = RenderManager::Get()->CreateMesh(t_positions);
}


RenderManager * RenderManager::Get()
{
    // Todo: safer handling when startup not called
    if (m_singleton != nullptr)
        return m_singleton;
    return nullptr;
}

void RenderManager::Startup()
{
    m_singleton = new RenderManager();
    RenderManager::Get()->m_shaderHandler = new ShaderHandler();
    RenderManager::Get()->DEBUGTriangleCreation();
}

void RenderManager::Render()
{
    // Set background color. Probably should be done here
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Start render with default shader
    glUseProgram(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader));

    // This treats the camera matrix as the world matrix. ONLY FOR TESTING PURPOSES!
    mat4x4 mvp = CameraManager::Get()->GetCameraMatrix();
    GLuint mvpHandle = glGetUniformLocation(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader), "MVP");
    glUniformMatrix4fv(mvpHandle, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 1); // Really hard coded.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    
}

