#include <ResourceManager.h>

int main()
{
    ResourceManager::Startup();
    ResourceManager* resMan = ResourceManager::Get();

    std::string fileNAme = "test";
    resMan->LoadChunk(fileNAme);

    int a = 3;
}