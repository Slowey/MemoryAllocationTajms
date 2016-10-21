#pragma once
#include <string> //Byt mot forward decl TODO
#include "EnumsAndDefines.h"
#include "MemoryTracker.h"
#include <vector>
#include <thread>

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

    void LoadChunk(const std::string & p_fileName, const std::string & p_subDirectory);

    void ResourceManager::LoadResource(const GUID &p_guid, const std::string & p_fileName);

    void ResourceManager::LoadResource(const GUID &p_guid, const std::string p_fileEnding, const std::string & p_fileName);

    std::string GetSavedPathFromGUID(const GUID &p_guid);

	/**
	Starts the DataManager
	*/
	static void Startup(size_t p_maximumMemoryUsage);

private:
	ResourceManager(size_t p_maximumMemoryUsage);
	~ResourceManager();
	static ResourceManager* m_singleton;
    PrioritizationManager* m_prioritizationManager;
	MemoryTracker* m_memoryTracker;

    std::vector<std::thread> m_threads;
};

