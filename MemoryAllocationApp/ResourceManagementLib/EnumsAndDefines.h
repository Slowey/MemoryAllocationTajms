#pragma once
#include <string>

enum PrioritizationAlgorithm
{
	LRU,
	FIFO,
	EXPLICIT
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

#define ERROR_GUID GUID(-1,-1)

struct ParserUID
{
    GUID guid;
    size_t parserHandle;
};
