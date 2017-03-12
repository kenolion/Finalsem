
#ifndef GAME_H
#define GAME_H
#define _USE_MATH_DEFINES
#include <cmath>
#include "constants.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include "Enemy.h"
#include "Pictures.h"
#include "Button.h"
class GameStateManager;

class Game		//
{
protected:
	HWND hwnd;
	
	D3DXVECTOR2 friction;
public:
	int framesToUpdate;
	bool initialize;
	void run(GameStateManager * game);
	virtual void deleteAll()=0;
	virtual bool initializeGame(HWND hwnd,GameStateManager* game) = 0;
	virtual void draw(GameStateManager * game)=0;
	virtual void update(int gameTime, GameStateManager * game) = 0;
	virtual void collisions(GameStateManager * game)=0;
	virtual void handleEvents(GameStateManager *game) = 0;

	int mouseX, mouseY;
protected:
	Game();
	~Game();
};

#endif // !GAME_H