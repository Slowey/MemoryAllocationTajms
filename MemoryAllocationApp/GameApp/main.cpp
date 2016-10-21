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
#include "main.h"
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
   MemoryManager::Startup(10240, 200000);
   ResourceManager::Startup(10000000); //Seet this lower to have memorytracker get full and start replacing stuff. Need to explicitly say that some resources are not used to actually replace. Otherwise crash


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
   
   GameObject* obj = new(objAllocator) GameObject(GUID(6355060461449191778, 9343578793668495956));
   GameObject* boy = new(objAllocator) GameObject(GUID(10501337584122868014, 4174563121594872176));
   GameObject* girl = new(objAllocator) GameObject(GUID(12148441303352944357, 8744070554219738464));
   boy->UpdatePosition(vec3(2,0,3));
   girl->UpdatePosition(vec3(-2, 0, 3));
   int first = 0;


   // Game loop
   while (true)
   {
      obj->Draw();
	  boy->Draw();
	  girl->Draw();
      Graphics::Get()->Update();
      first++;
      if (first == 1000)
      {
          ResourceManager::Get()->LoadChunk("tajms.tajms");
          //resMan->LoadChunk(fileName);
      }
   }
}