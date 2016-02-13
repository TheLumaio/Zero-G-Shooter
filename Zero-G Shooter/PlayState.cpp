#include "PlayState.h"

PlayState::PlayState()
{
}

PlayState::PlayState(Engine* e, const wchar_t* ip, const wchar_t* port, bool start_server) :
	GameState(e)
{
	wstring w_ip(ip);
	wstring w_port(port);
	m_ip = std::string(w_ip.begin(), w_ip.end());
	m_port = atoi(std::string(w_port.begin(), w_port.end()).c_str());
	m_start_server = start_server;
}

PlayState::~PlayState()
{
}

void PlayState::init(IrrlichtDevice* device, IVideoDriver* driver, ISceneManager* scene, IGUIEnvironment* gui)
{
	m_scene = scene;

	gui->addStaticText(L"CLIENT", rect<s32>(10, 10, 50, 22), true);
	timer = 0;

	if (m_start_server)
	{
		gui->addStaticText(L"SERVER", rect<s32>(10, 30, 50, 42), true);
		printf("[PLAY] start_server = true\n");
		m_server = new Server();
		m_server->start(27015);
	}
	m_client = new Client();
	m_client->start(m_ip, m_port);

	m_camera = scene->addCameraSceneNodeFPS();

}

void PlayState::leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*)
{

}

void PlayState::update(float dt)
{
	for (auto &it : m_client->getPeers())
	{
		Peer peer = (Peer)it.second;
		
		if (it.first == m_client->getLocalID()) continue;

		if (!peer.has_mesh)
		{
			IAnimatedMesh* mesh = m_scene->getMesh("player.dae");
			ISceneNode* node = m_scene->addAnimatedMeshSceneNode(mesh);
			if (node)
				node->setMaterialFlag(EMF_LIGHTING, false);

			m_players.emplace(it.first, node);
		}
		else
		{
			m_players.at(it.first)->setPosition(vector3df(peer.x, peer.y, peer.z));
			m_players.at(it.first)->setRotation(vector3df(peer.rx, peer.ry, peer.rz));
		}
	}
}

void PlayState::createMesh(int hostid)
{

}
