#include "GameState.h"


GameState::GameState() : initialized(false) { }
GameState::GameState(Engine* e) : initialized(false) { m_engine = e; }
GameState::~GameState() {}

void GameState::init(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*) {}
void GameState::leave(IrrlichtDevice*, IVideoDriver*, ISceneManager*, IGUIEnvironment*) {}
void GameState::update(float) {}
