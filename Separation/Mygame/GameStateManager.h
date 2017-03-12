#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANGER_H
#include <Windows.h>
#include <vector>
#include "DxSound.h"
#include "UserInterface.h"
#include "Cursor.h"
#include "Graphics.h"
#include "GameTime.h"
#include "PlayerInput.h"
class Game;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	bool initialize(HWND hwnd);
	void changeState(Game *game,HWND hwnd);
	void pushState(Game *game, HWND hwnd);
	void handleEvents();
	void popState();
	void run();
	LPD3DXSPRITE sprite;
	Cursor *cursor;
	GameStates state;
	Graphics * graphics;
	GameTime *gameTime;
	PlayerInput *input;
	DxSound *sound;
	bool exit;
private:
	bool initialized;
	
	std::vector<Game*> games;
};

#endif