#include "Graphics.h"

#include <GL\glew.h>
#include <GL\freeglut.h>

Graphics* Graphics::m_singleton = nullptr;

Graphics * Graphics::Get()
{
   if (m_singleton == nullptr)
      m_singleton = new Graphics();
   return m_singleton;
}

Graphics::Graphics()
{
   int argc;
   char* argv;
   //glutInit(&argc, &argv);
}


Graphics::~Graphics()
{
}
