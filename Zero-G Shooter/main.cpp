#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <irrlicht.h>
#include "Engine.h"
#include "MenuState.h"


// remove console
//#ifdef _IRR_WINDOWS_
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
//#endif

int main()
{
	
	Engine* engine = new Engine{};
	printf("\n\n\n");
	engine->setState(new MenuState(engine));
	engine->start();

	//delete engine;
	//engine = nullptr;

	return 0;

}
