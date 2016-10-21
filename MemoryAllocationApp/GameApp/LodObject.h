#pragma once
#include "GameObject.h"
#include <vector>
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
class LodObject :
   public GameObject
{
public:
   LodObject();
   LodObject(GUID p_objectToLoad);
   ~LodObject();

   void Draw();
   void UpdateLod();

private:
   vector<LodTexture> m_textures;

   ParsedPng** m_texInFront;
   ParsedPng** m_texBehind;
};

