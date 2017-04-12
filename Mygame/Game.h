
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
	virtual void deleteAll() = 0;
	virtual bool initializeGame(HWND hwnd, GameEngine* game) = 0;
	virtual void draw(GameEngine * game) = 0;
	virtual void update(int gameTime, GameEngine * game) = 0;
	virtual void collisions(GameEngine * game, int gameTime) = 0;
	virtual void handleEvents(GameEngine *game) = 0;
	int findPath(D3DXVECTOR2 start, D3DXVECTOR2 target);
	GameObject *tiles[17][43];
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
	struct Node {
		Node *parent;
		bool walkability ;
		int id;
		int parentId;
		int col;
		int row;

		int gCost;
		int hCost;
		int getFCost() {
			return gCost + hCost;
		}
		int elementNo;

	}target,start,currentNode;
	int movementCostToNeighbour;
//	Node getNode(int id, std::vector<Node> vecNode);
	std::vector<Node> openList;
	std::vector<Node> closeList;
	std::vector<Node> neighbour;
	std::vector<Node> path;
	//std::vector<Node> blocks;
	Node *blocks[400];
	int nodeId;
	bool contains(Node &node, std::vector<Node> vecNode);
	int getDistance(Node &nodeA, Node & nodeB);
	void retracePath(Node &start, Node &end);

protected:
	
	Game();
	~Game();
};

#endif // !GAME_H