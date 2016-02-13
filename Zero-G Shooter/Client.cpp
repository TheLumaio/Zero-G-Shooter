#include "Client.h"

std::map<int, Peer> Client::m_peers;

tokens_t       Client::m_datastack;
std::string    Client::m_ip;
sf::UdpSocket* Client::m_socket;
int            Client::m_localid;
int            Client::m_port = 0;
bool           Client::m_running = false;

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
	m_socket->bind(sf::UdpSocket::AnyPort);

	char buffer[BUFFERSIZE];
	std::size_t data_size;
	sf::IpAddress sender;
	unsigned short port;

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
				std::string data = m_datastack[i];
				m_datastack.erase(m_datastack.begin() + i);
				m_socket->send(data.c_str(), data.length(), m_ip, m_port);
			}

			if (m_socket->receive(&buffer, BUFFERSIZE, data_size, sender, port) == sf::Socket::Done)
			{
				tokens_t tkns = tokenize(std::string(buffer));

				if (tkns[0] == "localid" && tkns.size() > 1)
				{
					printf("[CLIENT] Got local ID %d\n", std::atoi(tkns[1].c_str()));
					m_localid = std::atoi(tkns[1].c_str());
				}

				if (tkns[0] == "userconnect" && tkns.size() > 1)
				{
					printf("[CLIENT] Got user connect\n");
					Peer _temp;
					_temp.id = std::atoi(tkns[1].c_str());

					if (_temp.id == 1)
						_temp.ip = sender.getLocalAddress().toString();
					else
						_temp.ip = sender.getPublicAddress().toString();

					_temp.port = port;
					m_peers.emplace(_temp.id, _temp);
				}

				if (tkns[0] == "worldpacket")
				{
					Peer& _peer = m_peers.at(std::atoi(tkns[1].c_str()));

					_peer.x = std::atoi(tkns[2].c_str());
					_peer.y = std::atoi(tkns[3].c_str());
					_peer.z = std::atoi(tkns[4].c_str());

					_peer.x = std::atoi(tkns[5].c_str());
					_peer.y = std::atoi(tkns[6].c_str());
					_peer.z = std::atoi(tkns[7].c_str());
				}
			}

			accumulator -= dt;
			t += dt;
		}
	}

}

void Client::start(std::string ip, int port)
{
	m_ip = ip;
	m_port = port;
	m_running = true;
	sendData("userconnect");
	m_thread = new std::thread(&threadfunct);

}

void Client::sendData(std::string data)
{
	m_datastack.push_back(data);
}

std::map<int, Peer>& Client::getPeers()
{
	return m_peers;
}

int Client::getLocalID()
{
	return m_localid;
}
