// This class
#include "RenderManager.h"

// Third party
#include <SOIL\SOIL.h>

// Our stuff
#include "CameraManager.h"


// debug
#include <iostream>
#include "SDLManager.h"
using namespace std;

using namespace glm;

/**
Struct containing what we need to draw an object*/
struct DrawObject
{
   DrawObject(mat4x4 p_world, GLuint p_textureHandle)
      :world(p_world), textureHandle(p_textureHandle)
   {

   }
   mat4x4 world;
   GLuint textureHandle;

};

RenderManager* RenderManager::m_singleton = nullptr;

void RenderManager::AddMatrixToMeshDrawList(unsigned int p_meshID, glm::mat4x4 p_worldMatrix, unsigned int p_textureID)
{
   if (m_meshDrawLists.find(p_meshID) == m_meshDrawLists.end())
   {
      // Mesh didn't exist! We do nothing. This could be changed for debug assistance
      return;
   }

   m_meshDrawLists[p_meshID].push_back(DrawObject(p_worldMatrix, p_textureID));
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
   m_meshDrawLists[r_positionBuffer] = vector<DrawObject>();
   m_meshSizes[r_positionBuffer] = p_positions.size();
   return r_positionBuffer;
}

GLuint RenderManager::CreateMesh(std::vector<Vertex> p_vertices)
{
   GLuint r_positionBuffer;
   glGenBuffers(1, &r_positionBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, r_positionBuffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * p_vertices.size(), &p_vertices[0], GL_STATIC_DRAW);
   // Create empty draw list for new mesh
   m_meshDrawLists[r_positionBuffer] = vector<DrawObject>();
   m_meshSizes[r_positionBuffer] = p_vertices.size();
   return r_positionBuffer;
}

GLuint RenderManager::CreateTexture(void * p_textureData, int p_numBytes)
{
   // Magic soil thing that's really untested
   GLuint r_textureHandle = SOIL_load_OGL_texture_from_memory(
      reinterpret_cast<unsigned char*>(p_textureData),
      p_numBytes,
      SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
   //// Code to manually create an empty texture. Dumping this here sounds like a bood idea
   //glGenTextures(1, &r_textureHandle);
   ////glActiveTexture(GL_TEXTURE0); // Might be necessary
   //glBindTexture(GL_TEXTURE_2D, r_textureHandle);
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Might be needed
   ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Might be needed
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, p_texWidth, p_texHeight, 0, GL_RGBA, GL_FLOAT, NULL); // Last parameter is the data
   //
   ////glBindImageTexture(0, r_textureHandle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F); // Might be needed
   return r_textureHandle;
}

GLuint RenderManager::CreateTexture(const char * p_fileName)
{
   // Let soil do all the work
   GLuint r_texturehandle = SOIL_load_OGL_texture(p_fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
   if (0 == r_texturehandle)
   {
      // Shit went wrong. Error handling?
      printf("SOIL loading error: '%s'\n", SOIL_last_result());
   }
   return r_texturehandle;
}

void RenderManager::DEBUGTriangleCreation()
{
   //// Create vertex buffer
   //vector<vec3> t_positions;
   //t_positions.push_back(vec3(-0.5, -0.5, 1));
   //t_positions.push_back(vec3(0.5, -0.5, 1));
   //t_positions.push_back(vec3(0, 0.5, 1));
   //GLuint meshVBO = RenderManager::Get()->CreateMesh(t_positions);

   // Create new vertex buffer with vertices, not just positions
   vector<Vertex> t_vertices;
   t_vertices.push_back(Vertex(vec3(-0.5, -0.5, 1), vec3(0, 0, -1), vec2(-1, -1)));
   t_vertices.push_back(Vertex(vec3(0.5, -0.5, 1), vec3(0, 0, -1), vec2(1, -1)));
   t_vertices.push_back(Vertex(vec3(0, 0.5, 1), vec3(0, 0, -1), vec2(0, 1)));
   GLuint meshVBO = RenderManager::Get()->CreateMesh(t_vertices);

   // Create texture
   GLuint textureHandle = CreateTexture("../GraphicsLib/Resources/test.jpg");
    textureHandle = CreateTexture("../GraphicsLib/Resources/test_low.jpg");
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

   // Get camera matrix
   mat4x4 vp = CameraManager::Get()->GetCameraMatrix();

   // Start render with default shader
   GLuint t_shaderProgram = m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader);
   glUseProgram(t_shaderProgram);

   // Iterate over all meshes to draw them
   for (auto it = m_meshDrawLists.begin(); it != m_meshDrawLists.end(); ++it)
   {
      // Iterate over all matrices for current mesh
      size_t t_numMatrices = it->second.size();
      for (size_t i = 0; i < t_numMatrices; i++)
      {
         mat4x4 mvp = vp * it->second.at(i).world;
         GLuint mvpHandle = glGetUniformLocation(t_shaderProgram, "MVP");
         glUniformMatrix4fv(mvpHandle, 1, GL_FALSE, &mvp[0][0]);
         GLuint samplerHandle = glGetUniformLocation(t_shaderProgram, "sampler");
         glUniform1i(samplerHandle, 0); // 0 Is the gl texture's id (the 0 from GL_TEXTURE0) ... I think

         // Enable attribs
         glEnableVertexAttribArray(0); // Positions
         glEnableVertexAttribArray(1); // Normals
         glEnableVertexAttribArray(2); // Texture coordinates
         // Bind current buffer
         glBindBuffer(GL_ARRAY_BUFFER, it->first);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)24);

         // Activate texture
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, it->second.at(i).textureHandle);

         glDrawArrays(GL_TRIANGLES, 0, m_meshSizes[it->first]);
         glDisableVertexAttribArray(0);
         glDisableVertexAttribArray(1);
         glDisableVertexAttribArray(2);
      }
      // Clear draw list for this mesh
      it->second.clear();
   }



   //// HARD CODED SHIT BELOW! Draws a silly triangle
   //GLuint mvpHandle = glGetUniformLocation(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader), "MVP");
   //glUniformMatrix4fv(mvpHandle, 1, GL_FALSE, &vp[0][0]);
   //glUniform1i(1, 0);
   //
   //glEnableVertexAttribArray(0);
   //glEnableVertexAttribArray(1);
   //glEnableVertexAttribArray(2);
   //// Bind current buffer
   //glBindBuffer(GL_ARRAY_BUFFER, 1);
   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)24);
   //
   //glActiveTexture(GL_TEXTURE0);
   //glBindTexture(GL_TEXTURE_2D, 1);
   //
   //glDrawArrays(GL_TRIANGLES, 0, 3);
   //glDisableVertexAttribArray(0);

   //// HARD CODED SHIT BELOW! Draws a silly triangle
   //GLuint mvpHandle = glGetUniformLocation(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader), "MVP");
   //glUniformMatrix4fv(mvpHandle, 1, GL_FALSE, &vp[0][0]);
   //glUniform1i(1, 0);
   //
   //glEnableVertexAttribArray(0);
   //glEnableVertexAttribArray(1);
   //glEnableVertexAttribArray(2);
   //// Bind current buffer
   //glBindBuffer(GL_ARRAY_BUFFER, 1);
   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
   //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
   //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)24);
   //
   //glActiveTexture(GL_TEXTURE0);
   //glBindTexture(GL_TEXTURE_2D, 1);
   //
   //glDrawArrays(GL_TRIANGLES, 0, 3);
   //glDisableVertexAttribArray(0);




}

