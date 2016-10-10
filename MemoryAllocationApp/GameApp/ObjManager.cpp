#include "ObjManager.h"
#include <sstream>
#include <iostream>

ObjManager* ObjManager::m_singleton = nullptr;

ObjManager::ObjManager(): ParserAndContainer("obj")
{
    void* vp = static_cast<void*>(new std::string("Testing some shit!"));
    ParseAndSaveParsedData(vp, 1, 1);
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
    while (!stream.eof())
    { 
        std::string currentInstruction;
        stream >> currentInstruction;
        if (currentInstruction.compare("v") == 0)
        {
            // Vertex data found, make vec3

        }
        else if (currentInstruction.compare("vt") == 0)
        {
        }
        else if (currentInstruction.compare("vn") == 0)
        {

        }
        else if (currentInstruction.compare("f") == 0)
        {

        }
    }
}
