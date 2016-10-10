#include <ResourceManager.h>
#include <ParserAndContainerManager.h>
#include "ObjManager.h"

int main()
{
    ResourceManager::Startup();
    ResourceManager* resMan = ResourceManager::Get();
    ParserAndContainerManager::Initialize();
    ObjManager::Initialize();

    std::string fileNAme = "test.zip";
    resMan->LoadChunk(fileNAme);

    int a = 3;
}