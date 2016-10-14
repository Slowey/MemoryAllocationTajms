#pragma once
#include <string>
#include "../EnumsAndDefines.h"

class FileLoader
{
public:
    FileLoader(std::string &p_fileEnding);
    ~FileLoader();

    virtual void LoadFile(const std::string & p_fileName) = 0;
    virtual void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) = 0;
    virtual void LoadResource(GUID p_GUID, const std::string & p_directory) = 0;
};

