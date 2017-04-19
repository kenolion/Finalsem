#include "Game.h"
#include "GameEngine.h"
#include "Platform.h"

bool Game::contains(Node & node, std::vector<Node> vecNode)
{
	for (int i = 0; i < vecNode.size(); i++)
		if (node.id == vecNode[i].id) {
			node.elementNo = i;
			return true;
		}
	return false;
}

int Game::getDistance(Node & nodeA, Node & nodeB)
{
	int distanceY = abs(nodeA.row - nodeB.row);
	int distanceX = abs(nodeA.col - nodeB.col);
	if (distanceX > distanceY)
		return 14 * distanceY + 10 * (distanceX - distanceY);
	return 14 * distanceX + 10 * (distanceY - distanceX);


}

void Game::retracePath(Node &start, Node & end)
{
	Node trace = end;

	while (trace.id != start.id) {
		path.push_back(trace);
		trace = *trace.parent;
		std::cout << path.back().col << "       " << path.back().row << std::endl;



	}
	std::cout << path.back().parent->col << "       " << path.back().parent->row << std::endl;

}


void Game::initializeAstar()
{
	//int arrayRow = 0;
	//int arrayCol = 0;
	//for (int i = 0; i < TILEROW*TILECOLUMN ; i++) {
	//	blocks.push_back(Node());
	//	if (i > TILECOLUMN) {
	//		arrayRow += (i /TILECOLUMN);
	//		arrayCol = i % (TILECOLUMN);
	//	}
	//	else {
	//		arrayCol = i;
	//	}
	//	std::cout << arrayRow << std::endl;
	//	if (tileMap[arrayRow][arrayCol] == 0) {
	//		blocks[i].walkability = true;
	//	}
	//	else {
	//		blocks[i].walkability = false;
	//	}
	//	blocks[i].id = i;
	//	blocks[i].col = arrayCol;
	//	blocks[i].row = arrayRow;
	//	arrayRow = 0;
	//}
	/*currentNode = new Node;
	(GAME_HEIGHT / TILEHEIGHT)*(GAME_WIDTH / TILEWIDTH)
	start = new Node;
	target = new Node;*/
	for (int i = 0; i < (GAME_HEIGHT / TILEHEIGHT)*(GAME_WIDTH / TILEWIDTH); i++) {
		blocks[i] = new Node();
	}

}

void Game::freeAStar()
{
	for (int i = 0; i < (GAME_HEIGHT / TILEHEIGHT)*(GAME_WIDTH / TILEWIDTH); i++) {
		delete blocks[i];
	}
	//if (start != NULL) {
	//	/*dltPtr(currentNode);
	//	dltPtr(start);
	//	dltPtr(target);*/
	//}
}

void Game::run(GameEngine * game)	// This function is called repeatedly by main message loop
{
	framesToUpdate = game->gameTime->update();
	game->input->getInput();												//A function that detects for input 
	game->input->ReadMouse();												//Read the mouse Device
	game->input->convertRelativeToAbsolute();								//Converts Relative X and Y mouse position to Absolute position
	game->cursor->setPosition(game->input->GetMouseLocation().x, game->input->GetMouseLocation().y);		//Sets the Cursor Position to the Absolute MouseX and MouseY in the window.
	game->setDrawingPoint(0,0);
	std::cout << game->input->GetMouseLocation().x << "     " << std::endl;

	std::cout << game->input->GetMouseLocation().y << "     " << std::endl;
	collisions(game, framesToUpdate);
	update(framesToUpdate, game);
	draw(game);// draws the games graphics
}

bool Game::loadLevel()
{
	std::fstream tileMapLoader(mapName);

	if (tileMapLoader.fail()) {
		std::string error = "Please make sure " + mapName + " is in the game folder!";
		MessageBox(NULL, error.c_str(), "Error Loading Map", MB_OK);
		return false;
	}
	for (int row = 0; row < TILEROW; row++) {
		for (int collumn = 0; collumn < TILECOLUMN; collumn++) {
			tileMapLoader >> tileMap[row][collumn];
			tileMapLoader.get(tempChar);
		}
	}
	tileMapLoader.close();
	return true;
}

bool Game::isSolid(float x, int y)
{
	//std::cout << tileMap[x / TILEWIDTH][y / TILEHEIGHT] << "    "<< std::endl;
	if (tileMap[(int)x / TILEWIDTH][y / TILEHEIGHT] > 0) {

		return true;
	}

	return false;
}



bool Game::checkGround(GameObject * object, int xOffset, int yOffset)
{
	object->btmLeft = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.left + xOffset);
	object->btmRight = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.right + xOffset);
	
	//	std::cout << object->onGround << "           " << std::endl << object->btmRight << "           " << std::endl;
	if (object->btmLeft && object->btmRight) {
	object->setOnGround(true);
	//std::cout << object->collisionRect.bottom + yOffset << std::endl;;
		return true;
	}
	if (object->btmLeft && !object->topLeft) {
		object->setOnGround(true);
		return true;
	}
	if (object->btmRight && !object->topRight) {
		object->setOnGround(true);
		return true;
	}

	object->setOnGround(false);
	return false;

}

bool Game::checkCeiling(GameObject * object, int xOffset, int yOffset)
{
	object->topLeft = isSolid(object->collisionRect.top + yOffset , object->collisionRect.left + xOffset);
	object->topRight = isSolid(object->collisionRect.top +yOffset, object->collisionRect.right + xOffset);
	//	std::cout << (object->collisionRect.right + xOffset) / TILEHEIGHT << "           " << std::endl; //<< yOffset << "           " << std::endl;
	if (object->topLeft && object->topRight) {
		object->setAtCeiling(true);
		//std::cout << object->collisionRect.bottom + yOffset << std::endl;;
		return true;
	}
	if (object->topLeft && !object->btmLeft && !object->btmRight) {
		object->setAtCeiling(true);
		//std::cout << object->collisionRect.bottom + yOffset << std::endl;;
		return true;
	}
	if (object->topRight && !object->btmLeft && !object->btmRight) {
		object->setAtCeiling(true);
		//std::cout << object->collisionRect.bottom + yOffset << std::endl;;
		return true;
	}


	object->setAtCeiling(false);
	return false;
}

bool Game::checkRightSide(GameObject * object, int xOffset, int yOffset)
{
	object->topRight = isSolid(object->collisionRect.top+yOffset, object->collisionRect.right +xOffset);
	object->btmRight = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.right + xOffset);
	if (object->topRight && object->btmRight) {
		object->pushesRightWall = true;
		
		return true;
	}
	object->pushesRightWall = false;
	return false;

}

bool Game::checkLeftSide(GameObject * object, int xOffset, int yOffset)
{
	object->topLeft = isSolid(object->collisionRect.top + yOffset, object->collisionRect.left + xOffset);
	object->btmLeft = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.left + xOffset);
	if (object->topLeft && object->btmLeft) {
		object->pushesLeftWall = true;
		
		return true;
	}
	object->pushesLeftWall = false;
	return false;

}

void Game::initializeTiles(GameEngine*game)
{
	numOfTiles = 0;
	for (int row = 0; row < TILEROW; row++) {
		for (int collumn = 0; collumn < TILECOLUMN; collumn++) {

			if (tileMap[row][collumn] > 0) {
				//tiles[numOfTiles] = new Platform(collumn, row, D3DXVECTOR2(1.0f, 1.0f), 1, TILEWIDTH, TILEHEIGHT, tileMap[row][collumn]);
		
				tiles[row][collumn] = new Platform(collumn, row, D3DXVECTOR2(1.0f, 1.0f), 1, TILEWIDTH, TILEHEIGHT, tileMap[row][collumn],numOfTiles);
				tiles[row][collumn]->initialize(game->graphics->device3d, "sprite\\TileMap.png", 288, 480, 10, 6, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f);
				numOfTiles++;
			}
		}

	}


}

int Game::findPath(D3DXVECTOR2 startpoint, D3DXVECTOR2 end)
{
	/*
		for (int i = 0; i < (GAME_HEIGHT / TILEHEIGHT)*(GAME_WIDTH / TILEWIDTH); i++) {
			if (startpoint.x / TILEWIDTH == blocks[i]->col && startpoint.y / TILEHEIGHT == blocks[i]->row) {
				start = blocks[i];
			}
			if (end.x / TILEWIDTH == blocks[i]->col && end.y / TILEHEIGHT == blocks[i]->row) {
				target = blocks[i];
			}
		}
	*/
	nodeId = 1;
	start.col = startpoint.x / TILEWIDTH;
	start.row = startpoint.y / TILEHEIGHT;
	target.row = end.x / TILEWIDTH;
	target.col = end.y / TILEHEIGHT;
	if (tileMap[target.row][target.col] > 0) {
		return 0;
	}
	start.gCost = 0;
	start.hCost = 0;
	start.id = blocks[nodeId]->id = nodeId;
	blocks[nodeId]->col = start.col;
	blocks[nodeId]->row = start.row;
	blocks[nodeId]->walkability = true;
	start.walkability = true;
	std::cout << " START : " << start.col << " ," << start.row << "  " << std::endl;
	std::cout << " END : " << target.col << " ," << target.row << "  " << std::endl;
	openList.push_back(start);				// step 1. add start point to open list
	//openList.insert(*start);
	while (openList.size() > 0) {
		currentNode = openList[0];

		for (int i = 1; i < openList.size(); i++)
			if (openList[i].getFCost() < currentNode.getFCost() || (openList[i].getFCost() == currentNode.getFCost() && openList[i].hCost < currentNode.hCost)) {
				currentNode = openList[i];
			}
		if (contains(currentNode, openList)) {			//check if currentNode is inside and if it is inside i need to know what is his element number in order for me to delete
			openList.erase(openList.begin() + currentNode.elementNo);
		}
		//	openList.

		closeList.push_back(currentNode);
		//blocks.push_back(currentNode);
		if (currentNode.row == target.row && currentNode.col == target.col) {

			retracePath(start, currentNode);
			return 1;
		}

		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (x == 0 && y == 0)
					continue;
				//arrayRow += (i / (GAME_WIDTH / TILEWIDTH));
				//arrayCol = i % (GAME_WIDTH / TILEWIDTH);

				if (tileMap[currentNode.row + y][currentNode.col + x] == 0) {
					neighbour.push_back(Node());
					nodeId++;
					neighbour.back().walkability = blocks[nodeId]->walkability = true;
					neighbour.back().col = blocks[nodeId]->col = currentNode.col + x;
					neighbour.back().row = blocks[nodeId]->row = currentNode.row + y;
					//neighbour.back().parent = &closeList.back();//&blocks[((currentNode.row + x)*TILECOLUMN)+];

					neighbour.back().id = blocks[nodeId]->id = nodeId;

				}

			}
		}

		for (auto& neighbour : neighbour) {
			if (contains(neighbour, closeList))
				continue;

			movementCostToNeighbour = currentNode.gCost + getDistance(currentNode, neighbour);

			if (movementCostToNeighbour < neighbour.gCost || !contains(neighbour, openList)) 				// if neighbour not inside openlist
			{
				neighbour.gCost = blocks[neighbour.id]->gCost = movementCostToNeighbour;
				neighbour.hCost = blocks[neighbour.id]->hCost = getDistance(neighbour, target);
				neighbour.parentId = blocks[neighbour.id]->parentId = closeList.back().id;
				neighbour.parent = blocks[neighbour.parentId];
				blocks[neighbour.id]->parent = blocks[neighbour.parentId];
				if (!contains(neighbour, openList)) {
					openList.push_back(neighbour);

				}
				/*if (!(std::find(openList.begin(), openList.end(), neighbour) != openList.end())) {
					openList.push_back(neighbour);
				}*/

			}
		}






		//start.x = startpoint.x / TILEWIDTH;
		//start.y = startpoint.y / TILEHEIGHT;

		//target.x = end.x / TILEWIDTH;
		//target.y = end.y / TILEHEIGHT;

		//if (start.x == target.x && start.y == target.y) {
		//	return 1; // path found
		//}


	}
	//nodeId = 0;


	return 0;
}



Game::Game()
{

	initialize = false;

}


Game::~Game()
{

}
