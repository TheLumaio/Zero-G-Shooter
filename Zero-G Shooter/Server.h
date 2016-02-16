#pragma once

#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <chrono>
#include <stdarg.h>
#include <utility>
#include <chrono>
#include <SFML/Network.hpp>
#include "Packet.h"
#include "Peer.h"

#define BUFFERSIZE 128

using namespace std::chrono;

struct Data
{
	int id;
	sf::Packet data;
};

typedef std::vector<std::string> tokens_t;
typedef std::vector<Data> data_t;

class Server
{
private:
	static std::map<int, Peer*> m_peers;
	static sf::UdpSocket*       m_socket;
	static data_t               m_datastack;
	static int                  m_port;
	static bool                 m_running;

	std::thread* m_thread;

	static sf::Packet m_temppacket;

	template<typename T>
		static void TsendData(T);
		
	template<typename Arg, typename ...Args>
		static void RsendData(Arg, Args...);
		static void RsendData();

	template<typename ...Args>
		static void sendData(PACKET, int, Args...);

	static tokens_t tokenize(std::string);

	static void threadfunct();

public:
	Server();
	~Server();

	void start(int);

};

