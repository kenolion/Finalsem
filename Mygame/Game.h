
#ifndef GAME_H
#define GAME_H
#define _USE_MATH_DEFINES
#include <cmath>
#include "constants.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Node.h"

typedef int(*AI)(D3DXVECTOR2 start, D3DXVECTOR2 target, float xOffset, float yOffset, float spritesWidth, float spritesHeight);
class GameEngine;

class Game		//
{
protected:
	HWND hwnd;
	D3DXVECTOR2 friction;
public:
	static int clientType;				//1, server 2= client
	int framesToUpdate;
	bool initialize;
	void run(GameEngine * game);
	virtual void multiplayer(GameEngine * game );
	virtual void deleteAll()=0;
	virtual bool initializeGame(HWND hwnd,GameEngine* game) = 0;
	virtual void draw(GameEngine * game)=0;
	virtual void update(int gameTime, GameEngine * game) = 0;
	virtual void collisions(GameEngine * game, int gameTime) = 0;
	virtual void handleEvents(GameEngine *game) = 0;
	void assignInput(GameEngine *game);
	int findPath(GameObject * object, D3DXVECTOR2 target, float xOffset, float yOffset, float spritesWidth, float spritesHeight);
	GameObject *tiles[TILEROW][TILECOLUMN];
	GameObject *object[FLAPPYBIRDOBJECTS];
	std::string mapName;
	int tileMap[TILEROW][TILECOLUMN];
	int numOfTiles;
	char tempChar;
	bool loadLevel();
	bool isSolid(float x, int y);
	bool checkGround(GameObject *object, int xOffset, int yOffset);
	bool checkCeiling(GameObject *object, int xOffset, int yOffset);
	bool checkRightSide(GameObject *object, int xOffset, int yOffset);
	bool checkLeftSide(GameObject *object, int xOffset, int yOffset);
	D3DXVECTOR2 gravity;
	D3DXVECTOR2 lines[50];       //use for drawing lines
	int counter;			// used to count 1 second
	void initializeTiles(GameEngine*game);
	//ai path finding
	/*

	open list 
	close list
	what each array has are these data
	f score  // g+h 
	g score  // cost to move to next block					
	h score the cost to move on that point to the ending point
	ID?

	parent block (row,collumn data type or give each block ID)


	1.add start point to close list
	2.add the rest of the points to open list

	*/
	void initializeAstar();
	void freeAStar();
	Node target,start,currentNode;
	int movementCostToNeighbour;
//	Node getNode(int id, std::vector<Node> vecNode);
	std::vector<Node> openList;
	std::vector<Node> closeList;
	std::vector<Node> neighbour;

	//std::vector<Node> blocks;
	Node *blocks[400];
	int nodeId;
	bool contains(Node &node, std::vector<Node> vecNode);
	int getDistance(Node &nodeA, Node & nodeB);
	void retracePath(GameObject * object, Node &end, float xOffset, float yOFfset);

protected:
	
	Game();
	~Game();
};

#endif // !GAME_H