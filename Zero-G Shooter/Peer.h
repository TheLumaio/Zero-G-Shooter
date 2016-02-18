#pragma once

#include <iostream>

struct Peer
{
	// game data
	bool has_mesh = false;
	float x, y, z;
	float rx, ry, rz;
	std::string name;

	// peer data
	std::string ip;
	int port;
	int id;

	/// constructor
	Peer(std::string ip, int port, int id, std::string name="Wow User") :
		ip(ip),
		port(port),
		id(id),
		name(name),
		x(0),
		y(0),
		z(0),
		rx(0),
		ry(0),
		rz(0)
	{ }
};
