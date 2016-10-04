#pragma once
#include <string> //Fixa forward decl TODO
#include <unordered_map>
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

	// Adding a location of the resource to the unordered_map that contains all of the resource id to string location.
	void AddResource(std::string p_resourceLocation, void* p_data);
	// Removing the resource from the unordered_map that contains all the resource id to string location (if needed)
	void RemoveResource(std::string p_resourceLocation);
private:
    DataManager();
    ~DataManager();
	static DataManager* m_singleton;
	std::unordered_map<std::string, void*> m_resourceStringToVoidPtrMap;
	unsigned int m_nextPlaceInTheMap;


};

