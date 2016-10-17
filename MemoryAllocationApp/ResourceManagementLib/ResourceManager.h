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

    void LoadChunk(const std::string & p_fileName);

    // Load whole or sub part of chunk
    //void LoadChunk(const std::string & p_fileName, const std::string & p_subDirectory);

	/**
	Starts the DataManager
	*/
	static void Startup();

private:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* m_singleton;
    PrioritizationManager* m_prioritizationManager;
};

