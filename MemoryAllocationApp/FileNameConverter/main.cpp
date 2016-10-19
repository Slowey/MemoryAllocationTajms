
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
#include "TAJMSArchiver.h"

// H�RDKODAT lite h�r o d�r vilken folder som ska l�sas ifr�n. 
// ResourcesTajms �r det nu s� om du ska l�sa fr�n en annan folder �r det den du ska �ndra.
int main(int numArgs, char * args[])
{
    // Parse args
    std::string t_filePath = args[0];

    size_t t_pos = t_filePath.find_last_of("\\");
    if (t_pos == std::string::npos)
        t_pos = -1;
    
    t_pos++;
    std::string t_fileName = t_filePath.substr(t_pos);


	// Load every filename into a vector of strings.
	ExtraKlass extraKlass;
	std::vector<std::string> t_whatFilesToRead;
	//extraKlass.ReadEveryFileInTheFolder("ResourcesTajms\\*", t_whatFilesToRead, t_fileName);
	extraKlass.ReadEveryFileInTheFolder("\*", t_whatFilesToRead, t_fileName);

	std::ofstream myfile;
	myfile.open("ResourcesTajms/DebugFileMD5.txt");
	myfile.close();

    TAJMSArchiver tajmsArkWay = TAJMSArchiver();

    std::string t_outName = "tajms.tajms";
    tajmsArkWay.Archive(t_whatFilesToRead, t_outName);

    

	//std::string t_stringForFileNameConversion = "";
	//std::string t_stringForGUID = "";
	//unsigned int forLoopLength = t_whatFilesToRead.size();
	//for (size_t i = 0; i < forLoopLength; i++)
	//{
	//	t_stringForFileNameConversion = extraKlass.ReadFileAndReturnTheStringOfAllContent(t_whatFilesToRead[i]);
	//	t_stringForGUID = extraKlass.CreateGUID(t_whatFilesToRead[i], t_stringForFileNameConversion);
	//	extraKlass.WriteToDebugMDFiveFile(t_whatFilesToRead[i], t_stringForGUID);
	//	//extraKlass.RenameTextFile(t_whatFilesToRead[i], t_stringForGUID);
	//}

	return 0;
}

