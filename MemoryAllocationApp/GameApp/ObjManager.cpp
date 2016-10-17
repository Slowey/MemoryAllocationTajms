#include "ObjManager.h"
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <Graphics.h>
#include <EnumsAndDefines.h>

ObjManager* ObjManager::m_singleton = nullptr;

ObjManager::ObjManager(): ParserAndContainer("obj")
{ 
    std::stringstream myBasicOBJStream;
    myBasicOBJStream << "v -0.500000 -0.500000 0.500000\n";
    myBasicOBJStream << "v 0.500000 -0.500000 0.500000\n";
    myBasicOBJStream << "v -0.500000 0.500000 0.500000\n";
    myBasicOBJStream << "v 0.500000 0.500000 0.500000\n";
    myBasicOBJStream << "v -0.500000 0.500000 -0.500000\n";
    myBasicOBJStream << "v 0.500000 0.500000 -0.500000\n";
    myBasicOBJStream << "v -0.500000 -0.500000 -0.500000\n";
    myBasicOBJStream << "v 0.500000 -0.500000 -0.500000\n";
    
    myBasicOBJStream << "vt 0.000000 0.000000\n";
    myBasicOBJStream << "vt 1.000000 0.000000\n";
    myBasicOBJStream << "vt 0.000000 1.000000\n";
    myBasicOBJStream << "vt 1.000000 1.000000\n";

    myBasicOBJStream << "vn 0.000000 0.000000 1.000000\n";
    myBasicOBJStream << "vn 0.000000 1.000000 0.000000\n";
    myBasicOBJStream << "vn 0.000000 0.000000 -1.000000\n";
    myBasicOBJStream << "vn 0.000000 -1.000000 0.000000\n";
    myBasicOBJStream << "vn 1.000000 0.000000 0.000000\n";
    myBasicOBJStream << "vn -1.000000 0.000000 0.000000\n";

    myBasicOBJStream << "f 1/1/1 2/2/1 3/3/1\n";
    myBasicOBJStream << "f 3/3/1 2/2/1 4/4/1\n";
    myBasicOBJStream << "f 3/1/2 4/2/2 5/3/2\n";
    myBasicOBJStream << "f 5/3/2 4/2/2 6/4/2\n";
    myBasicOBJStream << "f 5/4/3 6/3/3 7/2/3\n";
    myBasicOBJStream << "f 7/2/3 6/3/3 8/1/3\n";
    myBasicOBJStream << "f 7/1/4 8/2/4 1/3/4\n";
    myBasicOBJStream << "f 1/3/4 8/2/4 2/4/4\n";
    myBasicOBJStream << "f 2/1/5 8/2/5 4/3/5\n";
    myBasicOBJStream << "f 4/3/5 8/2/5 6/4/5\n";
    myBasicOBJStream << "f 7/1/6 1/2/6 5/3/6\n";
    myBasicOBJStream << "f 5/3/6 1/2/6 3/4/6\n";
    std::string myBasicOBJ = myBasicOBJStream.str().c_str();      
    void* vp = const_cast<char*>( myBasicOBJ.c_str());
    m_dummyMesh = ParseDataAndSendToGraphic(vp);
    //delete vp; // Shouldn't delete things you haven't used new on
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

void ObjManager::ParseAndSaveParsedData(void* p_dataStart, const size_t &p_size, const GUID &p_guid)
{
    // see if we already have the resource and its not the dummy
    if (ResourceExist(p_guid))
    {
        // we already have the resource!
        return;
    }
    ParsedObj* newResource = ParseDataAndSendToGraphic(p_dataStart);
    // mutex::lock()
    m_objResources[p_guid] = newResource;
    // mutex::unlock()
}

ParsedObj** ObjManager::GetResource(const GUID & p_guid)
{
    while (m_objResources.count(p_guid) == 0)
    {
        // The resource doesn't exist.. :( Return debug shit)
        // if(mutex::try_lock())
        // {
        m_objResources[p_guid] = m_dummyMesh;
        // mutex::unlock();
        // Load(GUID);
        // break;
        // }
    }
    ResourceRequested(p_guid);
    return &m_objResources.at(p_guid);
}

bool ObjManager::ResourceExist(const GUID &p_guid)
{
    bool r_exists = m_objResources.count(p_guid) != 0 && m_objResources.at(p_guid) != m_dummyMesh;
    return r_exists;
}

void ObjManager::FreeResource(const GUID &p_guid)
{
    if (ResourceExist(p_guid))
    {
        // should call graphic manager to remove the gpu resource to...
        delete m_objResources.at(p_guid);
        m_objResources.erase(p_guid);
    }
}

ParsedObj* ObjManager::ParseDataAndSendToGraphic(void * p_dataStart)
{
    // Parsing of obj file format
    char* t_charData = static_cast<char*>(p_dataStart);
    std::string inputData = t_charData;
    //std::cout << inputData; // Too much output for BTH LOGGA
    std::istringstream stream(inputData);
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
            float x, y, z;
            stream >> x >> y >> z;
            vertexData.push_back(glm::vec3(x, y, z));
        }
        else if (currentInstruction.compare("vt") == 0)
        {
            // uv data found, make vec2
            float u, v;
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
    std::vector<Vertex> completedVertices;
    for (size_t i = 0; i < count; i++)
    {
        // -1 cuz obj starts at 1 and c++ at 0. [] on the second vector access since we know the size of them and shouldnt miss
        glm::vec3 vertexPosition = vertexData.at(vertexIndices[i] - 1);
        glm::vec2 vertexUVMap = uvMappingData.at(uvIndices[i] - 1);
        glm::vec3 vertexNormal = normalData.at(normalIndices[i] - 1);
        // push the completed vertex TODO should be a complete mesh data, not just pos
        completedVertices.push_back(Vertex(vertexPosition, vertexNormal, vertexUVMap));
    }

    // create a new resource
    ParsedObj* newResource = new ParsedObj();
    // Make graphics engine create the mesh, this return a unsigned int which we will use to access the resource
    if (completedVertices.size() > 40)
      newResource->graphicResourceID = Graphics::Get()->CreateMesh(completedVertices, true);
    else
       newResource->graphicResourceID = Graphics::Get()->CreateMesh(completedVertices, false);
    
    return newResource;
}
