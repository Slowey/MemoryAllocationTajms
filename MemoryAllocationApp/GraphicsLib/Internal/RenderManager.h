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

    /**
    Creates a mesh and returns the GLuint.*/
    GLuint CreateMesh(std::vector<glm::vec3>& p_positions);

    /**
    Takes the provided data and turns it into a
    texture on the GPU. Returns GLuint handle*/
    GLuint CreateTexture(void* p_textureData, int p_texWidth, int p_texHeight);

    /**
    Adds the matrix to draw list for given ID.
    If mesh with the ID doesn't exist, it does nothing.*/
    void AddMatrixToMeshDrawList(unsigned int p_meshID, glm::mat4x4 p_worldMatrix);

private:
    static RenderManager* m_singleton;
    RenderManager();
    ~RenderManager();

    std::unordered_map<unsigned int, std::vector<glm::mat4x4>> m_meshDrawLists;

    // Debug stuff
    void DEBUGTriangleCreation();
};