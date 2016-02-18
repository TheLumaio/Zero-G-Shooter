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

	m_loader = new MapLoader{};
}

PlayState::~PlayState()
{
}

void PlayState::init(IrrlichtDevice* device, IVideoDriver* driver, ISceneManager* scene, IGUIEnvironment* gui)
{
	device->getCursorControl()->setVisible(false);
	m_scene = scene;

	gui->addStaticText(L"CLIENT", rect<s32>(10, 10, 50, 22), true);
	timer = 0;

	if (m_start_server)
	{
		gui->addStaticText(L"SERVER", rect<s32>(10, 30, 50, 42), true);
		printf("[PLAY] start_server = true\n");
		m_server = new Server();
		m_server->start(m_port);
	}
	
	m_client = new Client();
	m_client->start(m_ip, m_port);

	m_camera = scene->addCameraSceneNodeFPS(0, 100.f, 0.1f);

	//scene->addLightSceneNode(0, vector3df(0, 0, 0), SColorf(1.f, 1.f, 1.f, 1.f), 100.f);

	m_loader->loadMap("data/maps/testmap.json", scene);

}

void PlayState::leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*)
{

}

void PlayState::update(float dt)
{
	for (auto &peer : m_client->getPeers())
	{
		
		if (peer.second->id == m_client->getLocalID())
		{
			continue;
		}

		if (!peer.second->has_mesh)
		{

			IAnimatedMesh* mesh = m_scene->getMesh("data/objects/player.dae");
			IAnimatedMeshSceneNode* node = m_scene->addAnimatedMeshSceneNode(mesh);
			if (node)
			{
				node->setMaterialFlag(EMF_LIGHTING, true);
				node->addShadowVolumeSceneNode();
				node->setScale(vector3df(-1, 1, -1));
			}

			m_players.emplace(peer.first, node);

			peer.second->has_mesh = true;
		}
		else
		{
			if (m_players.at(peer.first) != nullptr)
			{
				m_players.at(peer.first)->setPosition(vector3df(peer.second->x, peer.second->y, peer.second->z));
				m_players.at(peer.first)->setRotation(vector3df(peer.second->rx, peer.second->ry, peer.second->rz));
			}
		}
	}

	
	if (m_client->getLocalID() > 0) {
		m_client->sendData(P_WORLD,
			m_client->getLocalID(),

			m_camera->getPosition().X,
			m_camera->getPosition().Y,
			m_camera->getPosition().Z,

			m_camera->getRotation().X,
			m_camera->getRotation().Y,
			m_camera->getRotation().Z);
	}
		
		

}

void PlayState::createMesh(int hostid)
{

}
