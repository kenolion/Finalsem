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
#include <thread>

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
	HANDLE hThread;
	unsigned threadID;

	GameCamera *camera;
	Network *network;
	LPD3DXSPRITE sprite;
	GameObject *cursor;
	GameStates state;
	Graphics * graphics;
	GameTime *gameTime;
	PlayerInput *input;
	DxSound *sound;
	LRESULT winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::thread netThread;

	WPARAM wParam;
	std::vector<Game*> games;
	char keyboardbuffer;

	std::string ipAddress;
	std::string hostIpAddress;

	bool ipAddresslocked = true;
	bool hostIpAddresslocked = true;

	bool exit;
private:
	bool initialized;
	
	
};

#endif