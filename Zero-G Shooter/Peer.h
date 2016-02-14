#pragma once

#include <iostream>

struct Peer
{
	// game data
	bool has_mesh = false;
	float x, y, z = 0;
	float rx, ry, rz = 0;
	std::string name = "Test User";

	// peer data
	std::string ip;
	int port;
	int id;

	/// constructor
	Peer(std::string ip, int port, int id) :
		ip(ip),
		port(port),
		id(id)
	{ }
};
