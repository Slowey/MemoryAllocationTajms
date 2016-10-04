#include "Graphics.h"

Graphics* Graphics::m_singleton = nullptr;

Graphics * Graphics::Get()
{
   if (m_singleton == nullptr)
      m_singleton = new Graphics();
   return m_singleton;
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}
