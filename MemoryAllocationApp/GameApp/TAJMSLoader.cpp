#include "TAJMSLoader.h"
#include <iostream>
#include <EnumsAndDefines.h>
#include <ParserAndContainerManager.h>
#include <MemoryTracker.h>
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
        if (!t_parAndContMan.ShouldLoadResource(t_ending, t_headers[i].guid))
            continue;

        // Wait until we can allocate
        if (!MemoryTracker::Get()->CheckIfMemoryAvailable(t_headers[i].fileSize))
        {
            fclose(t_file);
            throw 1337;
        }

        // Read to buffer
        char* t_tempBuff = new char[t_headers[i].fileSize];
        size_t len =fread(t_tempBuff, t_headers[i].fileSize, 1, t_file);
        size_t t_fileSize = t_headers[i].fileSize;

        if (len)
        {
            t_parAndContMan.ParseByEnding(t_tempBuff, t_fileSize, t_ending, t_headers[i].guid);
        }

        MemoryTracker::Get()->AddMemoryUsage(-1 * t_headers[i].fileSize);
        delete t_tempBuff;
    }

    fclose(t_file);
}

void TAJMSLoader::LoadFile(const std::string & p_fileName, const std::string & p_subDirectory)
{

}

void TAJMSLoader::LoadResource(GUID p_GUID, const std::string & p_directory)
{

}
