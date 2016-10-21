#pragma once
#include "../FileLoader.h"
#include <unordered_map>
#include <mutex>

class FileLoaderManager
{
public:
    static FileLoaderManager* Get();
    static void Startup();
    void RegisterLoader(FileLoader * p_loader, std::string p_ending);
    void LoadChunk(const std::string & p_fileName);
    void LoadChunkWithSub(const std::string & p_fileName, const std::string & p_subDirectory);
    void LoadResource(GUID p_GUID, const std::string & p_directory);
    void LoadResourceWithEnding(GUID p_GUID, const std::string &p_fileEnding, const std::string & p_directory);


private:
    static FileLoaderManager* m_singleton;

    FileLoaderManager();
    ~FileLoaderManager();
    std::unordered_map<std::string, FileLoader*> m_endingToLoaderMap;
    std::shared_ptr<std::mutex> m_sharedMutex;
};