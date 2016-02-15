#pragma once

#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <chrono>
#include <stdarg.h>
#include <SFML/Network.hpp>
#include "Packet.h"
#include "Peer.h"

#define BUFFERSIZE 128

using namespace std::chrono;

typedef std::vector<std::string> tokens_t;
typedef std::vector<sf::Packet> datastack_t;

class Client
{
private:

	static std::map<int, Peer*> m_peers;

	static datastack_t    m_datastack;
	static std::string    m_ip;
	static sf::UdpSocket* m_socket;
	static int            m_localid;
	static int            m_port;
	static bool           m_running;

	std::thread* m_thread;

	static sf::Packet m_temppacket;

	static tokens_t tokenize(std::string);
	static void threadfunct();

	template<typename T>
	static void TsendData(T);

	template<typename Arg, typename ...Args>
	static void RsendData(Arg, Args...);
	static void RsendData();

public:
	Client();
	~Client();

	template<typename ...Args>
		void sendData(PACKET, Args...);

	void start(std::string, int);

	std::map<int, Peer*>& getPeers();
	int getLocalID();

};

