#include "Server.h"

std::map<int, Peer*> Server::m_peers;
sf::UdpSocket*       Server::m_socket;
data_t               Server::m_datastack;
int                  Server::m_port = 0;
bool                 Server::m_running = false;
sf::Packet           Server::m_temppacket;

Server::Server()
{
}

Server::~Server()
{
}

template<typename T>
	void Server::TsendData(T t)
{
	m_temppacket << t;
}

template<typename Arg, typename ...Args>
	void Server::RsendData(Arg arg, Args... args)
{
	TsendData(arg);
	RsendData(args...);
}
void Server::RsendData() { }

template<typename ...Args>
	void Server::sendData(PACKET type, int id, Args... args)
{

	m_temppacket.clear();
	m_temppacket << type;

	RsendData(args...);

	Data _temp;
	_temp.id = id;
	_temp.data = m_temppacket;
	m_datastack.push_back(_temp);
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

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;

	int type;
	int id;
	int _id;
	
	while (m_running)
	{
		int i = 0;
		while (!m_datastack.empty())
		{
			auto& packet = m_datastack.at(0);

			sf::Packet p = packet.data;
			Peer* to_peer = m_peers.at(packet.id);

			m_socket->send(p, to_peer->ip, to_peer->port);
			m_datastack.erase(m_datastack.begin());

			i++;
		}

		/// receive packet data
		if (m_socket->receive(packet, sender, port) == sf::Socket::Done)
		{
			packet >> type;
			switch (type)
			{
			case P_USERCONNECT:
				std::cout << "[SERVER] user connected. " << sender.getLocalAddress().toString() << ":" << port << std::endl;
				// create peer
				_id = m_peers.size() + 1;
				std::cout << sender.toString() << std::endl;

				if (_id == 1)
					m_peers.emplace(_id, new Peer(sender.getLocalAddress().toString(), port, _id));
				else
					m_peers.emplace(_id, new Peer(sender.toString(), port, _id));

				sendData(P_LOCALID, _id, _id);

					/// tell everyone about new client
				for (auto& peer : m_peers)
					sendData(P_USERCONNECT, peer.second->id, _id);
				/// tell new client about everyone
				for (auto& peer : m_peers)
					if (peer.second->id != _id)
						sendData(P_USERCONNECT, _id, peer.second->id);
				/// 0
				break;

			case P_WORLD:
				float x, y, z, rx, ry, rz;
				packet >> id >> x >> y >> z >> rx >> ry >> rz;

				for (auto& peer : m_peers)
					if (peer.second->id != id)
						sendData(P_WORLD, peer.second->id, id, x, y, z, rx, ry, rz);

				break;

			default:
				break;
			}
		}

	}

}

void Server::start(int port)
{
	m_port = port;
	m_running = true;
	m_thread = new std::thread(&threadfunct);
}
