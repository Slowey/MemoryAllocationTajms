#pragma once
#include <string> //Byt mot forward decl TODO
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
	void FreeResource(std::string p_resource, const size_t& p_size);
	//void FreeResource(GUID p_guid); //TODO
};

