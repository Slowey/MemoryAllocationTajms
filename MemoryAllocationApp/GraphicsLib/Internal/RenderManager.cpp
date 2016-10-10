// This class
#include "RenderManager.h"

// Our stuff
#include "CameraManager.h"


// debug
#include <iostream>
#include "SDLManager.h"
using namespace std;

RenderManager* RenderManager::m_singleton = nullptr;

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
   return r_positionBuffer;
}

void RenderManager::DEBUGTriangleCreation()
{
      vector<vec3> t_positions;
      t_positions.push_back(vec3(-0.5, -0.5, 0));
      t_positions.push_back(vec3(0.5, -0.5, 0));
      t_positions.push_back(vec3(0, 0.5, 0));
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
    mat4x4 world = CameraManager::Get()->GetCameraMatrix();
    //mat4x4 world = mat4x4();
    glUniformMatrix4fv(
       glGetUniformLocation(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader),
          "world"), 1, GL_FALSE, 
       &world[0][0]);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 1); // Really hard coded.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    
}

