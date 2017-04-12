#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "Network.h"
#include "DxSound.h"
#include "Graphics.h"
#include "GameTime.h"
#include "PlayerInput.h"
#include "GameCamera.h"
#include "LevelMainMenu.h"

class Game;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	bool initialize(HWND hwnd);
	void changeState(Game *game,HWND hwnd);
	void pushState(Game *game, HWND hwnd);
	void handleEvents();
	void popState();
	void run();
	static void setDrawingPoint(int x, int y);
	
	GameCamera *camera;
	Network *network;
	LPD3DXSPRITE sprite;
	GameObject *cursor;
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