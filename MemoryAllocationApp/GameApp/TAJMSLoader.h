#pragma once
#include <fileloader.h>

class TAJMSLoader : public FileLoader
{
public:
    TAJMSLoader();
    ~TAJMSLoader();

    void LoadFile(const std::string & p_fileName) override;
    void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) override;
    void LoadResource(GUID p_GUID, const std::string & p_directory) override;

private:
    struct Header
    {
        GUID guid;
        char fileType[10]; // No mega fileendings
        size_t fileSize;
    };
};

