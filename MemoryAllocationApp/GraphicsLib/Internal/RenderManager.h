#pragma once
// Third Party
#include <glm/glm.hpp>
#include <GL2\glew.h>

// Standard libraries
#include <vector>

// Our stuff
#include "ShaderHandler.h"
#include "../Vertex.h"

// Forward declaration of internal draw object struct
struct DrawObject;

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
    Creates a mesh from a set of vertices and 
    returns the handle to the buffer.*/
    GLuint CreateMesh(std::vector<Vertex> p_vertices);

    /**
    Takes the provided data and turns it into a
    texture on the GPU. Returns GLuint handle*/
    GLuint CreateTexture(void* p_textureData, int p_numbBytes);

    /**
    Loads the specified file and converts it to
    a texture. Returns handle to texture*/
    GLuint CreateTexture(const char* p_fileName);

    /**
    Adds the matrix to draw list for given ID.
    If mesh with the ID doesn't exist, it does nothing.*/
    void AddMatrixToMeshDrawList(unsigned int p_meshID, glm::mat4x4 p_worldMatrix, unsigned int p_textureID);

private:
    static RenderManager* m_singleton;
    RenderManager();
    ~RenderManager();

    std::unordered_map<unsigned int, std::vector<DrawObject>> m_meshDrawLists;
    // Map to store how many vertices a mesh has
    std::unordered_map<unsigned int, unsigned int> m_meshSizes;

    // Debug stuff
    void DEBUGTriangleCreation();
};