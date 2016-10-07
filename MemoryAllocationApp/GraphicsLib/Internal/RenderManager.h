#pragma once
#include "ShaderHandler.h"

/**
Singleton to handle all mannger of rendering.
Specific work deligation isn't really decided yet...*/
class RenderManager
{
public:
    static RenderManager* Get();
    static void Startup();

private:
    static RenderManager* m_singleton;
    RenderManager();
    ~RenderManager();

    static ShaderHandler* m_shaderHandler;
};