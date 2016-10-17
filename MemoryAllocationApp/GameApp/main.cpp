#include <ResourceManager.h>
#include <ParserAndContainerManager.h>
#include <Graphics.h>
#include <thread>
#include <glm/gtc/matrix_transform.hpp>
#include "ObjManager.h"
#include "GameObject.h"
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


int main()
{
   ResourceManager::Startup();
   ResourceManager* resMan = ResourceManager::Get();
   ParserAndContainerManager::Initialize();


   int a = 3;
   Graphics::Startup();
   CreateWindow();

   ObjManager::Initialize();

   // We want to have started all parsers before we load the file x)

   thread m_loadThread;
   GameObject obj;
   int first = 0;
   // Game loop
   while (true)
   {
      obj.Draw();
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