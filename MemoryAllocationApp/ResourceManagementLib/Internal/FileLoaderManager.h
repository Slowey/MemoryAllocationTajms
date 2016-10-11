#pragma once
#include "FileLoader.h"
#include <unordered_map>

class FileLoaderManager
{
public:
    static FileLoaderManager* Get();
    static void Startup();
    void RegisterLoader(FileLoader * p_loader, std::string p_ending);
    void LoadChunk(std::string p_fileName);

private:
    static FileLoaderManager* m_singleton;

    FileLoaderManager();
    ~FileLoaderManager();

    std::unordered_map<std::string, FileLoader*> m_endingToLoaderMap;

};