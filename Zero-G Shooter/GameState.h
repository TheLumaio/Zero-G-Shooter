#pragma once

#include <iostream>
#include <irrlicht.h>
#include "Engine.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Engine;

class GameState
{
protected:
	Engine* m_engine;

public:
	bool initialized;

	GameState();
	GameState(Engine*);
	~GameState();

	virtual void init(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	virtual void leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	virtual void update(float);

};

