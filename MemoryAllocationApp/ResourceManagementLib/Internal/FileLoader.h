#pragma once
#include <string>

class FileLoader
{
public:
    FileLoader(std::string &p_fileEnding);
    ~FileLoader();

    virtual void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) = 0;
    virtual void LoadResource(int p_GUID) = 0; // Not sure if we should use this or only filename???
};

