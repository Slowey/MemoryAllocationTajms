#include "FileLoaderManager.h"

FileLoaderManager* FileLoaderManager::m_singleton = nullptr;

FileLoaderManager* FileLoaderManager::Get()
{
    return m_singleton;
}

void FileLoaderManager::Startup()
{
    if (m_singleton == nullptr)
    {
        m_singleton = new FileLoaderManager();
    }
}

FileLoaderManager::FileLoaderManager()
{
}

FileLoaderManager::~FileLoaderManager()
{
}

void FileLoaderManager::RegisterLoader(FileLoader* p_loader, std::string p_ending)
{
    // We can override the existing because if the user wants to use same ending but not our shipped loader(or is better at codign a loder then us x))
    m_endingToLoaderMap[p_ending] = p_loader;
}

void FileLoaderManager::LoadChunk(const std::string &p_fileName, const std::string &p_subDirectory)
{
    size_t t_lastDot = p_fileName.find_last_of(".");

    // No ending
    if (t_lastDot == std::string::npos)
        return;

    std::string t_ending = p_fileName.substr(t_lastDot + 1);


    // Find loader
    auto t_loader = m_endingToLoaderMap.find(t_ending);
    if (t_loader == m_endingToLoaderMap.end())
        return;

    t_loader->second->LoadFile(p_fileName, p_subDirectory);
}
