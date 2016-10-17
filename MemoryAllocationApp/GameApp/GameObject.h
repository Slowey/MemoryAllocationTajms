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
   ~GameObject();

   void Draw();

private:
   vec3 m_position;
   vec3 m_target;

   // Resource handles
   ParsedPng** m_textureHighID;
   ParsedObj** m_meshID;
};

