#pragma once
#include <string>

enum PrioritizationAlgorithm
{
	LRU,
	FIFO,
	EXPLICIT,
    LFU
};

struct GUID
{
	unsigned long long val[2];
	bool const operator==(const GUID &o)const {
		return val[0] == o.val[0] && val[1] == o.val[1];
	}
	bool const operator<(const GUID &o)const {
		return val[0] < o.val[0] || (val[0] == o.val[0] && val[1] < o.val[1]);
	}
    bool const operator!=(const GUID &o)const {
        return val[0] != o.val[0] || val[1] != o.val[1];
    }

    std::string ToString()
    {
        return std::to_string(val[0]) + "_" + std::to_string(val[1]);
     }

	GUID(long long p_valueOne, long long p_valueTwo)
	{
		val[0] = p_valueOne;
		val[1] = p_valueTwo;
	}
	GUID() {};

    GUID(std::string &p_idInString)
    {
        // 12321_1321321
        size_t split = p_idInString.find_last_of("_");
        std::string first = p_idInString.substr(0, split);
        std::string second = p_idInString.substr(split + 1);
        val[0] = stol(first);
        val[1] = stol(second);
    }


    
};

static bool ParseGUIDAndEndingFromFilePath(char* p_filePath, std::string *o_ending, GUID * o_outGuid)
{
	std::string t_fileNameString(p_filePath);
	size_t t_lastDot = t_fileNameString.find_last_of(".");

	// No ending
	if (t_lastDot == std::string::npos)
		return false;

	// Find start of name
	size_t t_beginning = t_fileNameString.find_last_of("/");
	if (t_beginning == std::string::npos)
		t_beginning = -1;

	// Increment because we dont want the slash in the name
	t_beginning++;
	*o_ending = t_fileNameString.substr(t_lastDot + 1);
	std::string t_name = t_fileNameString.substr(t_beginning, (t_lastDot - t_beginning));

	// We have decided to use split sign in ID, ask Techis & Jaws
	size_t t_idSplit = t_name.find_last_of("_");
	if (t_idSplit == std::string::npos)
		return false;

	*o_outGuid = GUID(t_name);
	return true;
}

#define ERROR_GUID GUID(-1,-1)

struct ParserUID
{
    GUID guid;
    size_t parserHandle;
};
