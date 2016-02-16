#pragma once

#include <iostream>

struct Peer
{
	// game data
	bool has_mesh = false;
	float x, y, z;
	float rx, ry, rz;
	std::string name = "Test User";

	// peer data
	std::string ip;
	int port;
	int id;

	/// constructor
	Peer(std::string ip, int port, int id) :
		ip(ip),
		port(port),
		id(id),
		x(0),
		y(0),
		z(0),
		rx(0),
		ry(0),
		rz(0)
	{ }
};
