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

    if (!t_file)
        return;

    // Write how big the header will be
    size_t t_size = p_filePaths.size();
    fwrite(&t_size, sizeof(size_t), 1, t_file);
    fpos_t t_headerPos;
    std::fgetpos(t_file, &t_headerPos);

    Header* t_headers = new Header[t_size]();
    
    // Move to files
    fwrite(t_headers, sizeof(Header), t_size, t_file);

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
        MD5 m_myFive = MD5(t_fileInString);
        t_headers[i].guid = m_myFive.GetResult();
        t_headers[i].p_fileSize = t_sizeEnd;

        // Write data
        fwrite(&t_fileInString[0], t_sizeEnd, 1, t_file);
    }

    fsetpos(t_file, &t_headerPos);
    fwrite(t_headers, sizeof(Header), t_size, t_file);
    fclose(t_file);
}
