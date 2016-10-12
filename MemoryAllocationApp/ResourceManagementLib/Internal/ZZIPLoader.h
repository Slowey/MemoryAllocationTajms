#pragma once
#include "FileLoader.h"
struct zzip_dirent;
struct zzip_dir;

class ZZIPLoader : public FileLoader
{
public:
    ZZIPLoader(std::string p_fileEnding);

    void LoadFile(const std::string & p_fileName) override;

    void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) override;

    void LoadResource(GUID p_GUID, const std::string & p_directory) override;




private:

    void LoadAndParseFile(zzip_dir * p_dir, const zzip_dirent & p_dirent);
};