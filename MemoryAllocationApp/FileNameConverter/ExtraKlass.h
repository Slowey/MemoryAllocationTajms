#pragma once

#include <map>
#include <iostream>
#include <memory>
#include "md5.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>
#include <string>
#include <wchar.h>

class ExtraKlass
{
public:
	ExtraKlass();
	~ExtraKlass();
	std::string CreateGUID(std::string p_fileLocation, std::string p_stringToMakeIntoGUID);
	std::string ReadFileAndReturnTheStringOfAllContent(std::string p_filename);
	std::vector<std::string> ReadTheNamesOfTheFilesToRead();
	void WriteToDebugMDFiveFile(std::string p_fileName, std::string p_mdfive);
	void RenameTextFile(std::string p_oldFileName, std::string p_newFileName);
	void ReadEveryFileInTheFolder(std::string p_directoryName, std::vector<std::string>& o_fileNamesInFolder);
private:
	std::string m_folderName = "ResourcesTajms/";
};

