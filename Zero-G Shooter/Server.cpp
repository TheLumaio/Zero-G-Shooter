#include "Server.h"

std::map<int, Peer> Server::m_peers;
sf::UdpSocket*      Server::m_socket;
data_t              Server::m_datastack;
int                 Server::m_port = 0;
bool                Server::m_running = false;

Server::Server()
{
}

Server::~Server()
{
}

void Server::sendData(std::string data, int id)
{
	Data _temp;
	_temp.id = id;
	_temp.data = data;
	m_datastack.push_back(_temp);
}

int Server::getPeerID(std::string ip, int port)
{
	for (auto &peer : m_peers)
		if (peer.second.ip == ip && peer.second.port == port)
			return peer.second.id;
	return -1;
}

tokens_t Server::tokenize(std::string str)
{
	tokens_t _temp;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, ' '))
		_temp.push_back(item);
	return _temp;
}

void Server::threadfunct()
{
	m_socket = new sf::UdpSocket();
	m_socket->setBlocking(true);
	m_socket->bind(m_port);

	char buffer[BUFFERSIZE];
	std::size_t data_size;
	sf::IpAddress sender;
	unsigned short port;
	int senderid;

	float t = 0.f;
	float dt = 1.f / 30.f;

	high_resolution_clock::time_point currentTime = high_resolution_clock::now();
	high_resolution_clock::time_point newTime;
	float accumulator = 0;

	while (m_running)
	{
		newTime = high_resolution_clock::now();
		double frametime = duration_cast<duration<double>>(newTime - currentTime).count();
		currentTime = newTime;
		accumulator += frametime;

		while (accumulator > dt)
		{
			for (int i = 0; i < m_datastack.size(); i++)
			{
				std::string data = m_datastack[i].data;
				int id = m_datastack[i].id;
				printf("[DATASTACK] %s : %d\n", data.c_str(), id);

				m_datastack.erase(m_datastack.begin() + i);

				m_socket->send(data.c_str(), data.length(), m_peers[id].ip, m_peers[id].port);
			}

			if (m_socket->receive(&buffer, BUFFERSIZE, data_size, sender, port) == sf::Socket::Done)
			{
				//senderid = getPeerID(sender.getLocalAddress().toString(), port);
				tokens_t tkns = tokenize(std::string(buffer));
				if (tkns.size() < 1)
					continue;

				if (tkns[0] == "userconnect")
				{
					Peer _temp;                                                                                                                                                                                                  
					_temp.id = m_peers.size() + 1;
					_temp.ip = sender.getLocalAddress().toString();
					_temp.port = port;
					m_peers.emplace(_temp.id, _temp);

					printf("[SERVER] addresses [%s] [%s]\n", sender.getLocalAddress().toString().c_str(), sender.getPublicAddress().toString().c_str());

					printf("[SERVER] Got user connect. [ID = %s] [PORT = %d]\n", _temp.ip.c_str(), _temp.port);

					sendData(std::string("localid ") + std::to_string(_temp.id), _temp.id);

					for (auto &peer : m_peers)
						sendData(std::string("userconnect ") + std::to_string(_temp.id), peer.second.id);
				}

				if (tkns[0] == "worldpacket")
				{
					for (auto &peer : m_peers)
						if (peer.second.id != std::atoi(tkns[1].c_str()))
							sendData(std::string(buffer), peer.second.id);
				}

			}

			accumulator -= dt;
			t += dt;
		}

	}

	printf("[SERVER] end\n");
}

void Server::start(int port)
{
	printf("[SERVER] start\n");
	m_port = port;
	m_running = true;
	m_thread = new std::thread(&threadfunct);
}
