#pragma once
#include "GameState.h"
#include "Engine.h"
#include "PlayState.h"

struct SAppContext
{
	IGUIEnvironment* gui;
	s32							 counter;
	IGUIListBox*		 listbox;
};

enum
{
	GUI_ID_SERVER_IP = 101,
	GUI_ID_SERVER_PORT,
	GUI_ID_SERVER_CONNECT,
	GUI_ID_SERVER_HOST
};

void enterPlayState(Engine*, const wchar_t*, const wchar_t*, bool);

class GuiReceiver : public IEventReceiver
{
private:
	IGUIEnvironment* gui;
	Engine* m_engine;

public:
	GuiReceiver(IGUIEnvironment* g, Engine* e) : gui(g) { m_engine = e; }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIElement* root = gui->getRootGUIElement();

			if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED && id == GUI_ID_SERVER_CONNECT)
			{
				auto x = rand() % 1200;
				auto y = rand() % 650;
				printf("%d:%d\n", x, y);

				enterPlayState(m_engine, root->getElementFromId(GUI_ID_SERVER_IP)->getText(), root->getElementFromId(GUI_ID_SERVER_PORT)->getText(), ((IGUICheckBox*)root->getElementFromId(GUI_ID_SERVER_HOST))->isChecked());
			}
		}

		return false;
	}
};

class MenuState : public GameState
{
private:

	IGUIEditBox* g_ip;
	IGUIEditBox* g_port;
	IGUIButton* g_conn;
	IGUICheckBox* g_host;

public:
	MenuState();
	MenuState(Engine*);
	~MenuState();

	void init(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*);
	void update(float);

};

