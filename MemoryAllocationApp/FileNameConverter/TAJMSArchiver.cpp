#include "TAJMSArchiver.h"
#include <iostream>
#include <fstream>


TAJMSArchiver::TAJMSArchiver()
{
}


TAJMSArchiver::~TAJMSArchiver()
{
}

void TAJMSArchiver::Archive(std::vector<std::string>& p_filePaths, std::string &p_outName)
{
    FILE* t_file;
    fopen_s(&t_file, p_outName.c_str(), "bw");

    // Write how big the header will be
    size_t t_size = p_filePaths.size();
    fwrite(&t_size, sizeof(size_t), 1, t_file);
    fpos_t t_headerPos, t_filePos;
    std::fgetpos(t_file, &t_headerPos);

    // Move to start of file to get position of it, not so nice way but doc said couln't read fpos_t directly
    for (size_t i = 0; i < t_size; i++)
    {
        Header t_emptyHead;
        fwrite(&t_emptyHead, sizeof(Header), 1, t_file);
    }
    
    // Get pos for files
    std::fgetpos(t_file, &t_filePos);

    // Now open each file
    for (size_t i = 0; i < t_size; i++)
    {
        // Places pointer at end of file, getting filesize.. but is a open
        std::ifstream t_curFile("example.bin", std::ios::in | std::ios::binary | std::ios::ate);

        // Get size of file (might only work on windows and binary mode :D)
        std::streampos t_sizeEnd = t_curFile.tellg();

        // Load file into memory
        std::string t_fileInString;
        t_fileInString.resize(t_sizeEnd);

        t_curFile.seekg(0, std::ios::beg);
        t_curFile.read(&t_fileInString[0], t_sizeEnd);
        t_curFile.close();
        
        // Get MD5
        Header t_head;
        MD5 m_myFive = MD5(t_fileInString);
        t_head.guid = m_myFive.GetResult();
        t_head.p_fileSize = t_sizeEnd;

        // Write header
        fsetpos(t_file, &t_headerPos);
        fwrite(&t_head, sizeof(Header), 1, t_file);
        std::fgetpos(t_file, &t_headerPos);

        // Write data
        fsetpos(t_file, &t_filePos);
        fwrite(&t_fileInString[0], t_sizeEnd, 1, t_file);
        std::fgetpos(t_file, &t_filePos);
    }
}
