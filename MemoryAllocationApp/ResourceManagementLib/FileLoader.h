#pragma once
#include <string>
#include "EnumsAndDefines.h"

/*
    Base class of loaders.
    Should contain:
    *LoadFile() 
        can call:
            ParseGUIDAndEndingFromFilePath() from EnumsAndDefines.h to get GUID and ending of a path
        Should call:
            ParserAndContainerManager.ShouldLoadResource() to check if need load on file
            while on MemoryTracker.CheckIfMemoryAvailable() until true
            then ParserAndContainerManager.ParseByEnding() to forward parsing
*/
class FileLoader
{
public:
    FileLoader(std::string p_fileEnding);
    ~FileLoader();

    virtual void LoadFile(const std::string & p_fileName) = 0;
    virtual void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) = 0;
    virtual void LoadResource(GUID p_GUID, const std::string & p_directory) = 0;
};

