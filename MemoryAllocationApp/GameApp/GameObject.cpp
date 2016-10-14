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
   m_textureHighID = 1;
   m_textureLowID = 2;
   m_meshID = 2;

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
   t_texId = t_dist > 5 ? m_textureLowID : m_textureHighID;
   cout << t_texId << endl;
   // Create world matrix and call draw object
   mat4x4 t_world = lookAt(m_position, m_position + m_target, vec3(0, 1, 0));
   Graphics::Get()->DrawObject(m_meshID, t_world, t_texId);
}
