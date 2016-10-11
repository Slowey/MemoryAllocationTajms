#pragma once
#include "FileLoader.h"


class ZZIPLoader : public FileLoader
{
public:
    ZZIPLoader(std::string p_fileEnding);

    void LoadFile(const std::string & p_fileName, const std::string & p_subDirectory) override;

    void LoadResource(int p_GUID) override;
};