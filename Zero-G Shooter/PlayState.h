#pragma once

#include <irrlicht.h>
#include "GameState.h"
#include "Server.h"
#include "Client.h"

class PlayState : public GameState
{
private:
	std::string m_ip;
	int m_port;
	bool m_start_server;

	Server* m_server;
	Client* m_client;

	float timer;

	// to use later because I'm lazy
	ISceneManager* m_scene;

	// Game objects
	std::map<int, ISceneNode*> m_players;
	ICameraSceneNode* m_camera;

public:
	PlayState();
	PlayState(Engine*, const wchar_t*, const wchar_t*, bool);
	~PlayState();

	void init(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void update(float);

	void createMesh(int);
};

