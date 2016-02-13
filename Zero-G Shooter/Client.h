#pragma once

#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <SFML/Network.hpp>
#include "Peer.h"

#define BUFFERSIZE 128

typedef std::vector<std::string> tokens_t;

class Client
{
private:

	static std::map<int, Peer> m_peers;

	static tokens_t       m_datastack;
	static std::string    m_ip;
	static sf::UdpSocket* m_socket;
	static int            m_localid;
	static int            m_port;
	static bool           m_running;

	std::thread* m_thread;

	static tokens_t tokenize(std::string);
	static void threadfunct();

public:
	Client();
	~Client();

	void start(std::string, int);
	void sendData(std::string);

	std::map<int, Peer>& getPeers();
	int getLocalID();

};

