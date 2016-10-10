#pragma once

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
	GUID(long long p_valueOne, long long p_valueTwo)
	{
		val[0] = p_valueOne;
		val[1] = p_valueTwo;
	}
	GUID() {};
};
struct ParserUID
{
    GUID guid;
    size_t parserHandle;
};
