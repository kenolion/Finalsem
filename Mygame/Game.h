
#ifndef GAME_H
#define GAME_H
#define _USE_MATH_DEFINES
#include <cmath>
#include "constants.h"
#include "GameObject.h"
#include <iostream>
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
	virtual void multiplayer(GameEngine * game );
	virtual void deleteAll()=0;
	virtual bool initializeGame(HWND hwnd,GameEngine* game) = 0;
	virtual void draw(GameEngine * game)=0;
	virtual void update(int gameTime, GameEngine * game) = 0;
	virtual void collisions(GameEngine * game,int gameTime)=0;
	virtual void handleEvents(GameEngine *game) = 0;
	GameObject *tiles[100];
	std::string mapName;
	int tileMap[TILEROW][TILECOLUMN];
	int numOfTiles;
	char tempChar;
	bool loadLevel();
	bool isSolid(float x, int y);
	bool checkGround(GameObject *object, int xOffset, int yOffset);
	bool checkCeiling(GameObject *object);
	bool checkRightSide(GameObject *object, int xOffset, int yOffset);
	bool checkLeftSide(GameObject *object, int xOffset, int yOffset);
	D3DXVECTOR2 gravity;
	void initializeTiles(GameEngine*game);
protected:
	Game();
	~Game();
};

#endif // !GAME_H