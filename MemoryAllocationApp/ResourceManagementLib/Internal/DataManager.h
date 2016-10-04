#pragma once
#include <string> //Fixa forward decl TODO

/**
This class will contain the map, hash table or w/e datastructure we end up using
to represent the GUID -> void*
It will have functionalioty to add and delete entries in the map.

*/

class DataManager
{
public:

	/**
	Gets a pointer to the DataManager singleton. Make sure Startup has
	been called!*/
	static DataManager* Get();

	/**
	Starts the DataManager
	*/
	static void Startup();

	void FreeResource(std::string p_resource, const size_t& p_size);
	//void FreeResource(GUID p_guid);

private:
    DataManager();
    ~DataManager();
	static DataManager* m_singleton;


};

