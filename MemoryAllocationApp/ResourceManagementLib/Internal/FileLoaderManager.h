#pragma once
#include "FileLoader.h"
#include <unordered_map>

class FileLoaderManager
{
public:
    static FileLoaderManager* Get();
    static void Startup(size_t p_maximumMemoryUsage);
    void RegisterLoader(FileLoader * p_loader, std::string p_ending);
    void LoadChunk(const std::string & p_fileName);
    void LoadChunk(const std::string & p_fileName, const std::string & p_subDirectory);

private:
    static FileLoaderManager* m_singleton;

    FileLoaderManager(size_t p_maximumMemoryUsage);
    ~FileLoaderManager();
	size_t m_maximumMemoryUsage;
    std::unordered_map<std::string, FileLoader*> m_endingToLoaderMap;

};