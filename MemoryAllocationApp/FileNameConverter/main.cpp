
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
#include "ExtraKlass.h"
// HÅRDKODAT lite här o där vilken folder som ska läsas ifrån. 
// ResourcesTajms är det nu så om du ska läsa från en annan folder är det den du ska ändra.
int main(int numArgs, char * args[])
{
	ExtraKlass extraKlass;

	// Load every filename into a vector of strings.
	std::vector<std::string> t_whatFilesToRead;
	extraKlass.ReadEveryFileInTheFolder("ResourcesTajms\\*", t_whatFilesToRead);
	
	std::ofstream myfile;
	myfile.open("DebugFileMD5.txt");
	myfile.close();



	std::string t_stringForFileNameConversion = "";
	std::string t_stringForGUID = "";
	unsigned int forLoopLength = t_whatFilesToRead.size();
	for (size_t i = 0; i < forLoopLength; i++)
	{
		t_stringForFileNameConversion = extraKlass.ReadFileAndReturnTheStringOfAllContent(t_whatFilesToRead[i]);
		t_stringForGUID = extraKlass.CreateGUID(t_whatFilesToRead[i], t_stringForFileNameConversion);
		extraKlass.WriteToDebugMDFiveFile(t_whatFilesToRead[i], t_stringForGUID);
		// extraKlass.RenameTextFile(t_whatFilesToRead[i], t_stringForGUID);
	}

	return 0;
}

