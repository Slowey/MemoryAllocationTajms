#pragma once

enum PrioritizationAlgorithm
{
	LRU,
	FIFO,
	EXPLICIT
};

typedef int GUID;
struct ParserUID
{
    GUID guid;
    size_t parserHandle;
};
