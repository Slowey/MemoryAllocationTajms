#include "TAJMSLoader.h"
#include <iostream>
#include <EnumsAndDefines.h>
#include <ParserAndContainerManager.h>
#include <string>



TAJMSLoader::TAJMSLoader() : FileLoader("tajms")
{
}


TAJMSLoader::~TAJMSLoader()
{
}

void TAJMSLoader::LoadFile(const std::string & p_fileName)
{
    ParserAndContainerManager& t_parAndContMan = ParserAndContainerManager::Get();
    FILE* t_file;
    fopen_s(&t_file, p_fileName.c_str(), "rb");

    if (!t_file)
        return;

    // Read how big the header is
    size_t t_size = 0;
    fread(&t_size, sizeof(size_t), 1, t_file);

    // Read headers
    Header* t_headers = new Header[t_size];
    fread(t_headers, sizeof(Header), t_size, t_file);
    
    // For each file
    for (size_t i = 0; i < t_size; i++)
    {
        // Get Ending
        std::string t_ending = t_headers[i].fileType;
        if (t_parAndContMan.ShouldLoadResource(t_ending, t_headers[i].guid))
        {



            t_parAndContMan.ParseByEnding()
        }


    }
}

void TAJMSLoader::LoadFile(const std::string & p_fileName, const std::string & p_subDirectory)
{

}

void TAJMSLoader::LoadResource(GUID p_GUID, const std::string & p_directory)
{

}
