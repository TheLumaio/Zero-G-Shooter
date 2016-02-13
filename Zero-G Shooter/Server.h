#pragma once

#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <chrono>
#include <SFML/Network.hpp>
#include "Peer.h"

#define BUFFERSIZE 128

using namespace std::chrono;

struct Data
{
	int id;
	std::string data;
};

typedef std::vector<std::string> tokens_t;
typedef std::vector<Data> data_t;

class Server
{
private:
	static std::map<int, Peer> m_peers;
	static sf::UdpSocket*      m_socket;
	static data_t              m_datastack;
	static int                 m_port;
	static bool                m_running;

	std::thread* m_thread;

	static void sendData(std::string, int id);
	static int getPeerID(std::string, int port);
	static tokens_t tokenize(std::string);
	static void threadfunct();

public:
	Server();
	~Server();

	void start(int);

};

