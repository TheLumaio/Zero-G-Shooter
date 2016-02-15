#include "Client.h"

std::map<int, Peer*> Client::m_peers;

datastack_t    Client::m_datastack;
std::string    Client::m_ip;
sf::UdpSocket* Client::m_socket;
int            Client::m_localid;
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

void Client::threadfunct()
{
	m_socket = new sf::UdpSocket();
	m_socket->setBlocking(true);

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	
	int type;

	while (m_running)
	{
		/// flush packets from stack
		for (int i = 0; i < m_datastack.size(); i++)
		{
			sf::Packet p = m_datastack.at(i);
			std::cout << "[SEND] " << p.getData() << ":" << p.getDataSize() << std::endl;
			m_socket->send(p, m_ip, m_port);
			m_datastack.erase(m_datastack.begin()+i);
		}

		/// receive packet data
		if (m_socket->receive(packet, sender, port) == sf::Socket::Done)
		{
			packet >> type;
			std::cout << "[CLIENT] got packet of type " << type << std::endl;
		}
	}

}

template<typename T>
	void Client::TsendData(T t)
{
	m_packet << t;
}

template<typename Arg, typename ...Args>
	void Client::RsendData(Arg arg, Args args)
{
	TsendData(T);
	RsendData(args...);
}
void Client::RsendData() { }

template<typename ...Args>
	void Client::sendData(PACKET type, Args... args)
{
	m_temppacket.clear();
	RsendData(args...);
	m_datastack.emplace_back(m_temppacket);
}

void Client::start(std::string ip, int port)
{
	m_ip = ip;
	m_port = port;
	m_running = true;
	sendData(P_USERCONNECT, -1);
	m_thread = new std::thread(&threadfunct);

}

std::map<int, Peer*>& Client::getPeers()
{
	return m_peers;
}

int Client::getLocalID()
{
	return m_localid;
}
