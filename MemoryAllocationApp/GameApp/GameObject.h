#pragma once
// Third party
#include <glm\glm.hpp>

#include "ObjManager.h"
using namespace glm;
/**
Simple game object that renders itself and such*/
class GameObject
{
public:
   GameObject();
   ~GameObject();

   void Draw();

private:
   vec3 m_position;
   vec3 m_target;

   // Resource handles
   unsigned int m_textureHighID;
   unsigned int m_textureLowID;
   ParsedObj** m_meshID;
};

