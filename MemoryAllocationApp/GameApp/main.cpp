#include <ResourceManager.h>
#include <ParserAndContainerManager.h>
#include <Graphics.h>
#include "ObjManager.h"

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
   std::string fileNAme = "test.zip";
   resMan->LoadChunk(fileNAme);


   while (true)
      Graphics::Get()->Update();
}