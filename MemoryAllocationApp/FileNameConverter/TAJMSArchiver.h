#pragma once
#include <vector>
#include <string>
#include "md5.h"

struct Header
{
    GUIDD guid;
    char fileType[10]; // No mega fileendings
    size_t fileSize;
};

class TAJMSArchiver
{
public:
    TAJMSArchiver();
    ~TAJMSArchiver();

    void Archive(std::vector<std::string>& p_filePaths, std::string & p_outName);
};

