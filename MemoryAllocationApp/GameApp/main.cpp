#include <ResourceManager.h>
#include <ParserAndContainerManager.h>
#include <Graphics.h>
#include <thread>
#include <glm/gtc/matrix_transform.hpp>
//#pragma comment (lib, "MemLib.lib")
#include <MemoryManager.h>
#include <PoolAllocator.h>
#include "ObjManager.h"
#include "GameObject.h"
#include "Global.h"
#include "TAJMSLoader.h"

using namespace std;
void CreateWindow()
{
   WindowParams params;
   params.argc = 0;
   params.argv = "";
   params.windowName = "Window Name";
   params.winPosX = 100;
   params.winPosY = 100;
   params.winSizeX = 1280;
   params.winSizeY = 720;
   Graphics::Get()->CreateWindow(params);
}

std::thread::id g_mainThread;

int main()
{
   ResourceManager::Startup(100000);
   MemoryManager::Startup(10240, 200000);
   g_mainThread = std::this_thread::get_id();
   ResourceManager* resMan = ResourceManager::Get();
   ParserAndContainerManager::Initialize();
   TAJMSLoader t_loader = TAJMSLoader();

   int a = 3;
   Graphics::Startup();
   CreateWindow();

   ObjManager::Initialize();
   PngManager::Initialize();

   // We want to have started all parsers before we load the file x)

   thread m_loadThread;
   
   PoolAllocator* objAllocator;
   objAllocator = MemoryManager::Get()->CreatePoolAllocator(sizeof(GameObject));
   
   GameObject* obj = new(objAllocator) GameObject();

   int first = 0;
   // Game loop
   while (true)
   {
      obj->Draw();
      Graphics::Get()->Update();
      first++;
      if (first == 1000)
      {
          std::string fileName = "test.zip";
          m_loadThread = thread(&ResourceManager::LoadChunk, resMan, fileName);
          //resMan->LoadChunk(fileName);
      }
   }
}