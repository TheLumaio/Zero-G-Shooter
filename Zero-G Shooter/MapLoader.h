#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>
#include <irrlicht.h>
#include <json.hpp>

using nlohmann::json;

class MapLoader
{
private:
	std::vector<irr::scene::ISceneNode*> m_lights;
	irr::scene::IAnimatedMeshSceneNode* m_map;

public:
	MapLoader();
	~MapLoader();

	void loadMap(std::string, irr::scene::ISceneManager*); // path to json map file

};

