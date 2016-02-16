#include "Client.h"

std::map<int, Peer*> Client::m_peers;

datastack_t    Client::m_datastack;
std::string    Client::m_ip;
sf::UdpSocket* Client::m_socket;
int            Client::m_localid = -1;
int            Client::m_port = 0;
bool           Client::m_running = false;
sf::Packet     Client::m_temppacket;

Client::Client()
{
}

Client::~Client()
{
}

tokens_t Client::tokenize(std::string str)
{
	tokens_t _temp;
	std::stringstream ss(str);
	std::string item;
	while (std::getline(ss, item, ' '))
		_temp.push_back(item);
	return _temp;
}

void Client::datafunct()
{
	while (m_running)
	{
		while (!m_datastack.empty())
		{
			auto& packet = m_datastack.at(0);
			m_socket->send(packet, m_ip, m_port);
			m_datastack.erase(m_datastack.begin());
		}
	}
}

void Client::threadfunct()
{
	m_socket = new sf::UdpSocket();
	m_socket->setBlocking(true);

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	
	int type;
	int id;

	while (m_running)
	{
		
		/// receive packet data
		if (m_socket->receive(packet, sender, port) == sf::Socket::Done)
		{
			packet >> type;
			switch (type)
			{
			case P_LOCALID:
				packet >> m_localid;
				std::cout << "[CLIENT] localid " << m_localid << std::endl;
				break;
			case P_USERCONNECT:
				packet >> id;
				m_peers.emplace(id, new Peer("", 0, id));

				std::cout << "[CLIENT] userconnect" << std::endl;
				break;

			case P_WORLD:
				float x, y, z, rx, ry, rz;
				packet >> id >> x >> y >> z >> rx >> ry >> rz;
				m_peers.at(id)->x = x;
				m_peers.at(id)->y = y;
				m_peers.at(id)->z = z;

				m_peers.at(id)->rx = rx;
				m_peers.at(id)->ry = ry;
				m_peers.at(id)->rz = rz;

			default:
				break;
			}
		}

	}

}

void Client::start(std::string ip, int port)
{
	m_ip = ip;
	m_port = port;
	m_running = true;
	m_thread = new std::thread(&threadfunct);
	sendData(P_USERCONNECT, -1);
	//m_datathread = new std::thread(&datafunct);

}

std::map<int, Peer*>& Client::getPeers()
{
	return m_peers;
}

int Client::getLocalID()
{
	return m_localid;
}
