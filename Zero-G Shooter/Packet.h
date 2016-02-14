#pragma once

#include <map>

enum PACKET
{
	P_USERCONNECT,
	P_LOCALID,
	P_WORLD,
};

static const std::map<PACKET, int> VARNUM = {
	{P_USERCONNECT, 1},
	{P_LOCALID, 1},
	{P_WORLD, 6}
};
