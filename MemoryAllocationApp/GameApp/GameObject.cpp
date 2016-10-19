// This class
#include "GameObject.h"

//Third party
#include <glm\gtx\transform.hpp>

// Our stuff
#include <Graphics.h>


// debug stuff
#include <iostream>
using namespace std;
// end debug

GameObject::GameObject()
{
   // Hard coded opengl handles
   m_textureHighID = PngManager::Get().GetResource(GUID(1338,1338));
   // This is bth logo
   m_meshID = ObjManager::Get().GetResource(GUID(1339,1339));

   m_position = vec3(0, 0, 5);
   m_target = vec3(0, 0, 1);
   
}


GameObject::~GameObject()
{
}

void GameObject::Draw()
{
   // Figure out if we want the low or high res texture
   vec3 t_playerPos = Graphics::Get()->GetCameraPosition();
   float t_dist = length(t_playerPos - m_position);
   unsigned int t_texId;
   t_texId = (*m_textureHighID)->graphicResourceID;
   //cout << t_texId << endl;
   // Create world matrix and call draw object
   vec3 t_scale = vec3(0.1f, 0.1f, 0.1f);
   mat4x4 t_scalemat = scale(t_scale);

   mat4x4 t_world = lookAt(m_position, m_position + m_target, vec3(0, 1, 0));
   t_world = t_world*t_scalemat;
   Graphics::Get()->DrawObject((*m_meshID)->graphicResourceID, t_world, t_texId);
}
