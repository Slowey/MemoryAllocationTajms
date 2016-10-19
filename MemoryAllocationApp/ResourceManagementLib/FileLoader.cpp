#include "FileLoader.h"
#include "Internal/FileLoaderManager.h"


FileLoader::FileLoader(std::string & p_fileEnding)
{
    //Save to where we keep track of loaders
    FileLoaderManager::Get()->RegisterLoader(this, p_fileEnding);
}

FileLoader::~FileLoader()
{
}
