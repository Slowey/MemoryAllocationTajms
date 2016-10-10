#pragma once
#include <string> //Byt mot forward decl TODO
#include "EnumsAndDefines.h"
class PrioritizationManager;
class ResourceManager
{
public:
	void FreeResource(GUID p_guid); //TODO
    /**
    Polymorphism to allow explicit resource freeing as well as implicit where prioalgo finds the best one to remove
    */
    void FreeResource();
	
	/**
	Gets a pointer to the DataManager singleton. Make sure Startup has
	been called!*/
	static ResourceManager* Get();

	/**
	Starts the DataManager
	*/
	static void Startup();


    // Temporary placeholder to test Loaders
    void LoadChunk(std::string &p_fileName);

private:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* m_singleton;
    PrioritizationManager* m_prioritizationManager;
};

