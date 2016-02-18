#pragma once

#include <irrlicht.h>
#include "GameState.h"
#include "Server.h"
#include "Client.h"
#include "MapLoader.h"

struct Player
{
	IBillboardTextSceneNode* nametag;
	ISceneNode* node;

	Player(IBillboardTextSceneNode* nametag, ISceneNode* node)
	{
		this->nametag = nametag;
		this->node = node;
	}

};

class PlayState : public GameState
{
private:
	std::string m_ip;
	std::string m_name;
	int m_port;
	bool m_start_server;

	IGUIFont* m_font;

	Server* m_server;
	Client* m_client;

	MapLoader* m_loader;

	float timer;

	// to use later because I'm lazy
	ISceneManager* m_scene;

	// Game objects
	std::map<int, Player*> m_players;
	ICameraSceneNode* m_camera;

public:
	PlayState();
	PlayState(Engine*, const wchar_t*, const wchar_t*, const wchar_t*, bool);
	~PlayState();

	void init(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void update(float);

	void createMesh(int);
};

