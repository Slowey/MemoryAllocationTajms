#include "TAJMSArchiver.h"
#include <iostream>
#include <fstream>
#include "ExtraKlass.h"


TAJMSArchiver::TAJMSArchiver()
{
}


TAJMSArchiver::~TAJMSArchiver()
{
}

void TAJMSArchiver::Archive(std::vector<std::string>& p_filePaths, std::string &p_outName)
{
    FILE* t_file = nullptr;
    fopen_s(&t_file, p_outName.c_str(), "wb");

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
    //for (size_t i = 0; i < t_size; i++)
    //{
        // Places pointer at end of file, getting filesize.. but is a open
        std::ifstream t_curFile = std::ifstream(p_filePaths[0].c_str(), std::ios::in | std::ios::binary | std::ios::ate);

        if (t_curFile)
            return;

        // Get size of file (might only work on windows and binary mode :D)
        int t_sizeEnd = t_curFile.tellg();

        // Load file into memory
        std::string t_fileInString;
        //////////////////////////////// NOT WORKING SOMETHING HERE SIZE NOT FIND FILE OR SOMETHING YY? U FIX? GOOD
        t_fileInString.resize(t_sizeEnd);

        t_curFile.seekg(0, std::ios::beg);
        t_curFile.read(&t_fileInString[0], t_sizeEnd);
        t_curFile.close();
        
        // Get MD5
        MD5 m_myFive = MD5(t_fileInString);


        // Get extension here
        size_t t_dotPos = p_filePaths[0].find_last_of(".");

        if (t_dotPos == std::string::npos)
            t_dotPos = -1;

        t_dotPos++;
        std::string t_fileExtension = p_filePaths[0].substr(t_dotPos);

        // Write data
        fwrite(&t_fileInString[0], t_sizeEnd, 1, t_file);

        // Add to header header
        t_headers[0].guid = m_myFive.GetResult();
        t_headers[0].fileSize = t_sizeEnd;
        memcpy(t_headers[0].fileType, &t_fileExtension, t_fileExtension.size() % 10);
    //}

    fsetpos(t_file, &t_headerPos);
    fwrite(t_headers, sizeof(Header), t_size, t_file);
    fclose(t_file);


    // Save headers to debug file
    ExtraKlass k = ExtraKlass();
    for (size_t i = 0; i < t_size; i++)
    {
        k.WriteToDebugMDFiveFile(p_filePaths[i], t_headers[i].guid.ToString());
    }
    

    delete t_headers;
}
