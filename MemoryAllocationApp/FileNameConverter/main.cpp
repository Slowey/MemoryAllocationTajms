
//#include "stdafx.h"
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

std::map<GUIDD, std::string> m_guidToString;
char* mdFiveGuid = new char[34];
std::string CreateGUID(std::string p_fileLocation, std::string p_stringToMakeIntoGUID)
{
	GUIDD t_guid;
	std::string r_guid = "";
	t_guid = md5(p_stringToMakeIntoGUID);

	m_guidToString.insert(std::pair<GUIDD, std::string>(t_guid, p_fileLocation));
	std::cout << "Guid: " << t_guid.val[0] << t_guid.val[1] << std::endl;
	std::cout << "Stringen: " << m_guidToString[t_guid] << std::endl;
	//r_guid = t_guid.val[0];// +t_guid.val[1];


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
std::string ReadFileAndReturnTheStringOfAllContent(std::string p_filename)
{
	std::ifstream myReadFile;
	std::string stringForConversion = "";
	char output[100000];
	myReadFile.open(p_filename);
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> output;

			// std::cout << output << std::endl;

			stringForConversion += output;
		}
	}
	myReadFile.close();
	//std::cout << stringForConversion;
	return stringForConversion;
}
// Reads from a text files what files want to be converted.
std::vector<std::string> ReadTheNamesOfTheFilesToRead()
{
	std::vector<std::string> r_whatFilesToRead;
	std::ifstream myReadFile;
	char output[100000];
	myReadFile.open("ResourcesTajms/WhatFilesToRead.txt");
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
void WriteToDebugMDFiveFile(std::string p_fileName, std::string p_mdfive)
{
	std::ofstream myfile;
	myfile.open("ResourcesTajms/DebugFileMD5.txt",std::fstream::app);
	myfile << p_fileName << ": " << p_mdfive << std::endl;
	myfile.close();
}
void RenameTextFile(std::string p_oldFileName, std::string p_newFileName)
{
	int result;
	const char *cstr = p_oldFileName.c_str();
	p_newFileName += ".txt";
	const char *secondConstCharForConversion = p_newFileName.c_str();
	result = rename(cstr, "hejsan.txt");
	if (result == 0)
	{
		puts("File successfully renamed");
	}
	else
	{
		perror("Error renaming file");
	}
}
// Example on how to write the directoy "ResourcesTajms\\*" this is how it is done.
void ReadEveryFileInTheFolder(std::string p_directoryName)
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
		std::cout << t_string << std::endl;
	}
	FindClose(hFind);	
	int holamuchocao = 0;
}
int main(int numArgs, char * args[])
{
	// Load every filename into a vector of strings.
	std::vector<std::string> t_whatFilesToRead;
	t_whatFilesToRead = ReadTheNamesOfTheFilesToRead();
	ReadEveryFileInTheFolder("ResourcesTajms\\*");
	
	std::ofstream myfile;
	myfile.open("ResourcesTajms/DebugFileMD5.txt");
	myfile.close();



	std::string t_stringForFileNameConversion = "";
	std::string t_stringForGUID = "";
	unsigned int forLoopLength = t_whatFilesToRead.size();
	for (size_t i = 0; i < forLoopLength; i++)
	{
		t_stringForFileNameConversion = ReadFileAndReturnTheStringOfAllContent(t_whatFilesToRead[i]);
		t_stringForGUID = CreateGUID(t_whatFilesToRead[i], t_stringForFileNameConversion);
		WriteToDebugMDFiveFile(t_whatFilesToRead[i], t_stringForGUID);
		RenameTextFile(t_whatFilesToRead[i], t_stringForGUID);
	}


	int hola = 2;
	return 0;
}

