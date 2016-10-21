#pragma once
#include "LodObject.h"
#include "GameObject.h"
#include <Graphics.h>
#include <vector>
using namespace std;

LodObject::LodObject()
{
}

LodObject::LodObject(GUID p_objectToLoad)
   :GameObject(p_objectToLoad)
{
   m_textures.push_back(LodTexture(1, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(2, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(3, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(4, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(5, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(6, GUID(7799555238942610605, 15628347817556400855)));
   m_textures.push_back(LodTexture(7, GUID(7799555238942610605, 15628347817556400855)));
}

LodObject::~LodObject()
{
}

void LodObject::Draw()
{
   GameObject::Draw();
}

void LodObject::UpdateLod()
{
   vec3 t_playerPos = Graphics::Get()->GetCameraPosition();
   float t_dist = length(t_playerPos - m_position);
}
