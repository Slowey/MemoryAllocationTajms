#pragma once
#include <map>
#include <string>
class LRUPriority
{
public:
	void UpdateMap(std::string);
	void AddToMap(std::string);
	std::string PopLeastRecentlyUsed();

	/**
	Starts the LRU algorithm as a singelton
	*/
	static void Startup();
	/**
    Gets a pointer to the LRUpriority singleton. Make sure Startup has
    been called!*/
	static LRUPriority* Get();
private:
	std::map<std::string, size_t>m_priorityMap;
	LRUPriority();
	~LRUPriority();
	static LRUPriority* m_singleton;

};