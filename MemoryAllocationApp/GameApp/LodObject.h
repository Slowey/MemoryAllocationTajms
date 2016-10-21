#pragma once
#include <vector>
#include "ObjManager.h"
#include "PngManager.h"
#include <glm\glm.hpp>
using namespace glm;
using namespace std;
struct LodTexture
{
   LodTexture(float p_dist, GUID p_textureID)
      :distance(p_dist), textureID(p_textureID)
   {

   }
   float distance;
   GUID textureID;
};
class LodObject
{
public:
   LodObject();
   LodObject(GUID p_objectToLoad);
   ~LodObject();

   void Draw();
   void UpdateLod();

private:
   vector<LodTexture> m_textures;

   int m_currentLod;

   vec3 m_position;
   vec3 m_target;
   vec3 m_up;

   ParsedObj** m_mesh;

   ParsedPng** m_currentTexture;
   ParsedPng** m_closerTexture;
   ParsedPng** m_furtherTexture;

   GUID m_currentTextureID;
   GUID m_closerTextureID;
   GUID m_furtherTextureID;
   
};

