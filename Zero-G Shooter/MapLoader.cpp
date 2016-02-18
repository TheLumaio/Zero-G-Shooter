#include "MapLoader.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

void MapLoader::loadMap(std::string jsonfile, irr::scene::ISceneManager* scene)
{
	std::ifstream _stream(jsonfile);
	std::string _contents;

	// load json data into string
	_stream.seekg(0, std::ios::end);
	_contents.reserve(_stream.tellg());
	_stream.seekg(0, std::ios::beg);

	_contents.assign((std::istreambuf_iterator<char>(_stream)),
		std::istreambuf_iterator<char>());

	// create json object
	auto mapdata = json::parse(_contents);

	// erase old map
	if (m_map != nullptr)
	{
		m_map->remove();
		delete m_map;
		m_map = nullptr;
	}

	// load map node
	std::string _filename = mapdata["map"];
	m_map = scene->addAnimatedMeshSceneNode(scene->getMesh(_filename.c_str()));;
	m_map->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	m_map->addShadowVolumeSceneNode();
	scene->setShadowColor(irr::video::SColor(150, 0, 0, 0));

	
	// load lights
	for (auto& light : mapdata["lights"])
	{
		float x = light["x"];
		float y = light["y"];
		float z = light["z"];
		float lumin = 10.f; //light["lumin"];

		float r = (float)rand() / RAND_MAX;
		float g = (float)rand() / RAND_MAX;
		float b = (float)rand() / RAND_MAX;
		std::cout << r << " " << g << " " << b << std::endl;

		m_lights.push_back(scene->addLightSceneNode(0, irr::core::vector3df(x, y, z), irr::video::SColorf(r, g, b, 1.f), lumin));

	}


}
