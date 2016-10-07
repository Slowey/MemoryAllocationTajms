#pragma once
#include <string> //Byt mot forward decl TODO
class ResourceManager
{
public:
	void FreeResource(std::string p_resource, const size_t& p_size);
	//void FreeResource(GUID p_guid); //TODO
	
	/**
	Gets a pointer to the DataManager singleton. Make sure Startup has
	been called!*/
	static ResourceManager* Get();

	/**
	Starts the DataManager
	*/
	static void Startup();

	void ReferencePing(/*GUID p_id*/);

private:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* m_singleton;
};

