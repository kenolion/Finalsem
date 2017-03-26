
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
#include <fstream>

class GameEngine;

class Game		//
{
protected:
	HWND hwnd;
	
	D3DXVECTOR2 friction;
public:
	
	int framesToUpdate;
	bool initialize;
	void run(GameEngine * game);
	virtual void deleteAll()=0;
	virtual bool initializeGame(HWND hwnd,GameEngine* game) = 0;
	virtual void draw(GameEngine * game)=0;
	virtual void update(int gameTime, GameEngine * game) = 0;
	virtual void collisions(GameEngine * game)=0;
	virtual void handleEvents(GameEngine *game) = 0;
	GameObject *tiles[100];
	std::string mapName;
	int tileMap[TILEROW][TILECOLUMN];
	int numOfTiles;
	char tempChar;
	bool loadLevel();
	void initializeTiles(GameEngine*game);
	int mouseX, mouseY;
protected:
	Game();
	~Game();
};

#endif // !GAME_H