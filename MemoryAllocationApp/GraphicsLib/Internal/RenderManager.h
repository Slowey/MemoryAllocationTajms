#pragma once
// Third Party
#include <glm/glm.hpp>
#include <GL2\glew.h>

// Standard libraries
#include <vector>

// Our stuff
#include "ShaderHandler.h"

/**
Singleton to handle all mannger of rendering.
Specific work deligation isn't really decided yet...*/
class RenderManager
{
public:
    static RenderManager* Get();
    static void Startup();
    void Render();
    // Public pointers. This was easiest
    ShaderHandler* m_shaderHandler;

    GLuint CreateMesh(std::vector<glm::vec3>& p_positions);

private:
    static RenderManager* m_singleton;
    RenderManager();
    ~RenderManager();

    

    // Debug stuff
    void DEBUGTriangleCreation();
};