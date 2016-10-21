#pragma once
// Third party
#include <glm\glm.hpp>

#include "ObjManager.h"
#include "PngManager.h"
using namespace glm;
/**
Simple game object that renders itself and such*/
class GameObject
{
public:
   GameObject();
   GameObject(GUID p_objectToLoad);
   ~GameObject();

   void UpdatePosition(vec3 p_pos);

   void Draw();

protected:
   vec3 m_position;
   vec3 m_target;

   // Resource handles
   ParsedPng** m_textureHighID;
   ParsedObj** m_meshID;
};

