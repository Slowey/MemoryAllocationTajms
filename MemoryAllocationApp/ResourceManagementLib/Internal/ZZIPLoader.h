#pragma once
#include "FileLoader.h"


class ZZIPLoader : public FileLoader
{
public:
    ZZIPLoader(std::string p_fileEnding);

    void LoadFile(std::string p_fileName) override;
    void LoadResource(int p_GUID) override;
};