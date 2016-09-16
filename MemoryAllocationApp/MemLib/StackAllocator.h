#pragma once
class StackAllocator
{
    virtual int TestMethod() = 0;
};

enum class Stack
{
	LongTerm,
	MidTerm,
	ShortTerm,
};