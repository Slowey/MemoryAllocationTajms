#include "ObjManager.h"
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <Graphics.h>

ObjManager* ObjManager::m_singleton = nullptr;

ObjManager::ObjManager(): ParserAndContainer("obj")
{
    void* vp = static_cast<void*>(new std::string("f 1/2/3 4/5/6 7/8/9"));
    //ParseAndSaveParsedData(vp, 1, 1);
    delete vp;
}


ObjManager::~ObjManager()
{
}

void ObjManager::Initialize()
{
    if (m_singleton != nullptr)
    {
        // already initialized
        throw 1337;
    }
    m_singleton = new ObjManager();
}

ObjManager & ObjManager::Get()
{
    if (m_singleton == nullptr)
    {
        // Not yet initialized
        throw 1337;
    }
    return *m_singleton;
}

void ObjManager::ParseAndSaveParsedData(void * p_dataStart, size_t p_size, GUID p_guid)
{
    // Parsing of obj file format
    std::string* inputData = static_cast<std::string*>(p_dataStart);
    std::cout << *inputData;
    std::istringstream stream(*inputData);
    std::vector<glm::vec3> vertexData;
    std::vector<glm::vec2> uvMappingData;
    std::vector<glm::vec3> normalData;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    while (!stream.eof())
    { 
        std::string currentInstruction;
        stream >> currentInstruction;
        if (currentInstruction.compare("v") == 0)
        {
            // Vertex data found, make vec3
            float x,y,z;
            stream >> x >> y >> z;
            vertexData.push_back(glm::vec3(x, y, z));
        }
        else if (currentInstruction.compare("vt") == 0)
        {
            // uv data found, make vec2
            float u,v;
            stream >> u >> v;
            uvMappingData.push_back(glm::vec2(u, v));
        }
        else if (currentInstruction.compare("vn") == 0)
        {
            // normal data found, make vec3
            float nx, ny, nz;
            stream >> nx >> ny >> nz;
            normalData.push_back(glm::vec3(nx, ny, nz));
        }
        else if (currentInstruction.compare("f") == 0)
        {
            // Guessing its only three connected vertexpoints (No quads allowed here!)
            for (size_t i = 0; i < 3; i++)
            {
                // three ints for saving the connected vertex, normal and uvmap
                unsigned int vertexIndex, uvIndex, normalIndex;
                // Reading three connected things, v/u/n
                std::string connectedData;
                stream >> connectedData;
                // scan the given string since its in format v/u/n
                sscanf_s(connectedData.c_str(), "%d/%d/%d", &vertexIndex, &uvIndex, &normalIndex);
                // insert info into vectors
                vertexIndices.push_back(vertexIndex);
                uvIndices.push_back(uvIndex);
                normalIndices.push_back(normalIndex);
            }
        }
    }
    // all data should now be read, processing starts here TODO could be done during reading of faces
    // go thorugh all the faces, doesnt matter which indices vector we take, they are all the same size
    size_t count = vertexIndices.size();
    // TODO should be a complete mesh data, not just pos
    std::vector<glm::vec3> completedVerices;
    for (size_t i = 0; i < count; i++)
    {
        // -1 cuz obj starts at 1 and c++ at 0. [] on the second vector access since we know the size of them and shouldnt miss
        glm::vec3 vertexPosition = vertexData.at(vertexIndices[i] - 1);
        glm::vec2 vertexUVMap = uvMappingData.at(uvIndices[i] - 1);
        glm::vec3 vertexNormal = normalData.at(normalIndices[i] - 1);
        // push the completed vertex TODO should be a complete mesh data, not just pos
        completedVerices.push_back(vertexPosition);
    }
}
