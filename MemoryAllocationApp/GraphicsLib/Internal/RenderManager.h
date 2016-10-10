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
    ShaderHandler* m_shaderHandler;

private:
    static RenderManager* m_singleton;
    RenderManager();
    ~RenderManager();

    GLuint CreateMesh(std::vector<glm::vec3>& p_positions);

    // Debug stuff
    void DEBUGTriangleCreation();
};