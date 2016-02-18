#include "MenuState.h"

MenuState::MenuState() { }
MenuState::MenuState(Engine* e) : GameState(e) { }
MenuState::~MenuState() { }

void MenuState::init(IrrlichtDevice* device, IVideoDriver* driver, ISceneManager* scene, IGUIEnvironment* gui)
{
	SAppContext context;
	context.gui = gui;
	context.counter = 0;
	context.listbox = nullptr;

	device->setEventReceiver(new GuiReceiver(gui, m_engine));

	printf("initializing ...\n");
	g_ip = gui->addEditBox(L"localhost", rect<s32>(100, 100, 200, 122), true, 0, GUI_ID_SERVER_IP);
	g_port = gui->addEditBox(L"27015", rect<s32>(200, 100, 300, 122), true, 0, GUI_ID_SERVER_PORT);
	g_name = gui->addEditBox(L"Name", rect<s32>(300, 100, 400, 122), true, 0, GUI_ID_NAME);
	g_conn = gui->addButton(rect<s32>(100, 130, 200, 152), 0, GUI_ID_SERVER_CONNECT, L"Connect", L"Connect to server using above settings");
	g_host = gui->addCheckBox(true, rect<s32>(100, 75, 200, 102), 0, GUI_ID_SERVER_HOST, L"Host Server");
}

void MenuState::leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*)
{
	g_ip->remove();
	g_port->remove();
	g_name->remove();
	g_conn->remove();
	g_host->remove();
}

void MenuState::update(float)
{

}

void enterPlayState(Engine* e, const wchar_t* ip, const wchar_t* port, const wchar_t* name, bool start_server)
{
	e->setState(new PlayState(e, ip, port, name, start_server));
}
