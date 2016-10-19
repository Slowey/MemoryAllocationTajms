#include "ExtraKlass.h"



ExtraKlass::ExtraKlass()
{
}


ExtraKlass::~ExtraKlass()
{
}
std::map<GUIDD, std::string> m_guidToString;
std::string ExtraKlass::CreateGUID(std::string p_fileLocation, std::string p_stringToMakeIntoGUID)
{
	GUIDD t_guid;
	std::string r_guid = "";
	t_guid = md5(p_stringToMakeIntoGUID);

	m_guidToString.insert(std::pair<GUIDD, std::string>(t_guid, p_fileLocation));
	std::cout << "Guid: " << t_guid.val[0] << t_guid.val[1] << std::endl;
	std::cout << "Stringen: " << m_guidToString[t_guid] << std::endl;

	std::string number;
	std::stringstream strstream;
	strstream << t_guid.val[0];
	strstream >> number;
	r_guid += number;

	strstream << t_guid.val[1];
	strstream >> number;
	r_guid += number;

	return r_guid;
}
// Reading the content of all the files that has been added to the list. The files in this list will have their name converted to md5.
std::string ExtraKlass::ReadFileAndReturnTheStringOfAllContent(std::string p_filename)
{
	std::ifstream myReadFile;
	std::string stringForConversion = "";
	char output[100000];
	myReadFile.open(m_folderName + p_filename);
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> output;
			stringForConversion += output;
		}
	}
	myReadFile.close();
	return stringForConversion;
}
// Reads from a text files what files want to be converted.
std::vector<std::string> ExtraKlass::ReadTheNamesOfTheFilesToRead()
{
	std::vector<std::string> r_whatFilesToRead;
	std::ifstream myReadFile;
	char output[100000];
	myReadFile.open(m_folderName + "WhatFilesToRead.txt");
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> output;
			r_whatFilesToRead.push_back(output);
		}
	}
	myReadFile.close();


	return r_whatFilesToRead;
}
void ExtraKlass::WriteToDebugMDFiveFile(std::string p_fileName, std::string p_mdfive)
{
	std::ofstream myfile;
	myfile.open(m_folderName + "DebugFileMD5.txt", std::fstream::app);
	myfile << p_fileName << ": " << p_mdfive << std::endl;
	myfile.close();
}
void ExtraKlass::RenameTextFile(std::string p_oldFileName, std::string p_newFileName)
{
    std::string t_stringForOldFileName = m_folderName;
    t_stringForOldFileName += p_oldFileName;
    const char *cstr = t_stringForOldFileName.c_str();
    std::string t_stringForNameChanging = m_folderName;
    t_stringForNameChanging += p_newFileName;
    t_stringForNameChanging += ".txt";
    const char *secondConstCharForConversion = t_stringForNameChanging.c_str();
    rename(cstr, secondConstCharForConversion);
}
// Example on how to write the directoy "ResourcesTajms\\*" this is how it is done.
void ExtraKlass::ReadEveryFileInTheFolder(std::string p_directoryName, std::vector<std::string> &o_fileNamesInFolder, const std::string &p_excludeFile)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	std::wstring t_wstringFileName(p_directoryName.begin(), p_directoryName.end());
	LPCWSTR wildcard = (t_wstringFileName).c_str();
	hFind = FindFirstFile(wildcard, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}
	FindNextFile(hFind, &FindFileData);
	while (FindNextFile(hFind, &FindFileData))
	{
		std::wstring t_wstring(FindFileData.cFileName);
		std::string t_string(t_wstring.begin(), t_wstring.end());
        if (t_string != p_excludeFile && t_string != "DebugFileMD5.txt")
        {
            o_fileNamesInFolder.push_back(t_string);
        }
    }
	FindClose(hFind);
}