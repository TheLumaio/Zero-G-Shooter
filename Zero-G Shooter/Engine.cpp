#include "Engine.h"

Engine::Engine()
{
	m_device = createDevice(EDT_OPENGL, dimension2d<u32>(1280, 720), 32, false, true, true, 0);
	m_device->setWindowCaption(L"Multiplayer Space Deathmatch");

	m_driver = m_device->getVideoDriver();
	m_scene = m_device->getSceneManager();
	m_gui = m_device->getGUIEnvironment();

}

void Engine::start()
{
	while (m_device->run())
	{
		if (!m_states.empty())
		{
			if (!m_states.top()->initialized)
			{
				m_states.top()->init(m_device, m_driver, m_scene, m_gui);
				m_states.top()->initialized = true;
			}
		}

		if (!m_states.empty())
			m_states.top()->update(1.f / 512.f);

		m_driver->beginScene(true, true, SColor(255, 110, 100, 101));

		m_scene->drawAll();
		m_gui->drawAll();

		m_driver->endScene();
	}
}

void Engine::setState(GameState* state)
{
	printf("new state: ");
	if (!m_states.empty())
	{
		printf(" !empty\n");
		m_states.top()->leave(m_device, m_driver, m_scene, m_gui);
		delete m_states.top();
		m_states.top() = nullptr;
		m_states.pop();
	}
	printf("clear.\n");
	m_states.push(state);
}

