#pragma once

#include <iostream>
#include <stack>
#include <irrlicht.h>
#include "GameState.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GameState;

class Engine
{
private:
	IrrlichtDevice* m_device;
	IVideoDriver* m_driver;
	ISceneManager* m_scene;
	IGUIEnvironment* m_gui;

	stack<GameState*> m_states;

public:
	Engine();
	~Engine()=default;

	void start();
	void setState(GameState*);
};

