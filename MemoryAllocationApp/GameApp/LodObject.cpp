#pragma once
#include "LodObject.h"
#include "GameObject.h"
#include <Graphics.h>
#include <vector>
#include <glm\gtx\transform.hpp>
using namespace std;

#include <iostream>
using namespace std;

LodObject::LodObject()
{
   m_currentLod = 0;
}

LodObject::LodObject(GUID p_objectToLoad)
{

   m_mesh = ObjManager::Get().GetResource(GUID(p_objectToLoad));
   

   m_position = vec3(0, 0, 3);
   m_target = vec3(0, 0, 1);

   // Ordered by proximity: closest texture first
   //m_textures.push_back(LodTexture(1, GUID(4508368927262052700, 10709386060134965090))); // Real first level
   m_textures.push_back(LodTexture(1, GUID(12541587199237929205, 11674305702883187293)));
   m_textures.push_back(LodTexture(2, GUID(18139683254994884314, 18292644416606165182)));
   m_textures.push_back(LodTexture(3, GUID(9401606901309987613, 1073637065706517070)));
   m_textures.push_back(LodTexture(4, GUID(4855936038678453222, 8196177433684602735)));
   m_textures.push_back(LodTexture(5, GUID(5342444162030727833, 17680151873040685426)));
   m_textures.push_back(LodTexture(6, GUID(3382445088593843835, 6549905152913186843)));
   m_textures.push_back(LodTexture(7, GUID(11283779729541403127, 5041571205266230584)));

   m_currentLod = 0;

   // Set start lod
   vec3 t_playerPos = Graphics::Get()->GetCameraPosition();
   float t_dist = length(t_playerPos - m_position);

   for (size_t i = 0; i < m_textures.size(); i++)
   {
      // Check level
      if (t_dist < m_textures.at(i).distance)
      {
         
         m_currentLod = i;
         m_currentTextureID = m_textures.at(i).textureID;
         m_currentTexture = PngManager::Get().GetResource(m_currentTextureID);
         if (i < m_textures.size() - 1)
         {
            m_furtherTextureID = m_textures.at(i+1).textureID;
            m_furtherTexture = PngManager::Get().GetResource(m_furtherTextureID);
         }
         if (i > 0)
         {
            m_closerTextureID = m_textures.at(i-1).textureID;
            m_closerTexture = PngManager::Get().GetResource(m_closerTextureID);
         }
         break;
      }
   }

}

LodObject::~LodObject()
{
}

void LodObject::Draw()
{
   unsigned int t_texId;
   t_texId = (*m_currentTexture)->graphicResourceID;

   // Create world matrix and call draw object
   vec3 t_scale = vec3(0.1f, 0.1f, 0.1f);
   mat4x4 t_scalemat = scale(t_scale);

   mat4x4 t_world = lookAt(m_position, m_position + m_target, vec3(0, 1, 0));
   t_world = t_world*t_scalemat;
   Graphics::Get()->DrawObject((*m_mesh)->graphicResourceID, t_world, t_texId);
   //Graphics::Get()->DrawObject(1, t_world, t_texId);

}

void LodObject::UpdateLod()
{
   vec3 t_playerPos = Graphics::Get()->GetCameraPosition();
   float t_dist = length(t_playerPos - m_position);

   // Iterate through all levels
   for (size_t i = 0; i < m_textures.size(); i++)
   {
      // Check level
      if (t_dist < m_textures.at(i).distance)
      {
         // Moved away from object
         if (i > m_currentLod)
         {

            cout << "moved away to level: " << i << endl;
            /// New closer
            // Unload old closer
            if (i > 0)
            {
               //PngManager::Get().ReleaseResource(m_textures.at(i - 1).textureID);
               PngManager::Get().ReleaseResource(m_closerTextureID); // Same as code commented above
            }
            // Update new closer to previous current
            m_closerTextureID = m_currentTextureID;
            m_closerTexture = m_currentTexture;

            /// Handle new current
            m_currentTexture = m_furtherTexture;
            m_currentTextureID = m_furtherTextureID;

            /// New further
            if (i < m_textures.size() - 1)
            {
               // Update ID
               m_furtherTextureID = m_textures.at(i + 1).textureID;
               // Load it
               m_furtherTexture = PngManager::Get().GetResource(m_furtherTextureID);
            }

         }
         // Moved towards object
         else if (i < m_currentLod)
         {
            cout << "moved closer to level: " << i << endl;
            /// New further
            // Unload old further
            if (i < m_textures.size()-1)
            {
               //PngManager::Get().ReleaseResource(m_textures.at(i - 1).textureID);
               PngManager::Get().ReleaseResource(m_furtherTextureID); // Same as code commented above
            }
            // Update new closer to previous current
            m_furtherTextureID = m_currentTextureID;
            m_furtherTexture = m_currentTexture;

            /// Handle new current
            m_currentTexture = m_closerTexture;
            m_currentTextureID = m_closerTextureID;

            /// New closer
            if (i > 0)
            {
               // Update ID
               m_closerTextureID = m_textures.at(i - 1).textureID;
               // Load it
               m_closerTexture = PngManager::Get().GetResource(m_closerTextureID);
            }
         }
         else
         {
            // do nothing
         }
         m_currentLod = i;
         break;
      }
   }

}
