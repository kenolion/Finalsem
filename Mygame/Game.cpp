#include "Game.h"
#include "GameEngine.h"
#include "Platform.h"
int Game::clientType;


void Game::run(GameEngine * game)	// This function is called repeatedly by main message loop
{
	framesToUpdate = game->gameTime->update();
	game->input->getInput();												//A function that detects for input 
	game->input->ReadMouse();												//Read the mouse Device
	game->input->convertRelativeToAbsolute();								//Converts Relative X and Y mouse position to Absolute position
	game->cursor->setPosition(game->input->GetMouseLocation().x, game->input->GetMouseLocation().y);		//Sets the Cursor Position to the Absolute MouseX and MouseY in the window.
	assignInput(game);
	game->network->sendData(clientType);
	//std::cout << mouseX << "     " << mouseY << "      " << std::endl;
	multiplayer(game);
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
	object->topLeft = isSolid(object->collisionRect.top + yOffset, object->collisionRect.left + xOffset);
	object->topRight = isSolid(object->collisionRect.top + yOffset, object->collisionRect.right + xOffset);
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
	object->topRight = isSolid(object->collisionRect.top + yOffset, object->collisionRect.right + xOffset);
	object->btmRight = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.right + xOffset);
	object->middleRight = isSolid(object->collisionRect.bottom - (object->getHeight() / 2) + yOffset, object->collisionRect.right + xOffset);
	if (object->topRight && object->btmRight && !object->pushesLeftWall) {
		object->pushesRightWall = true;

		return true;
	}
	if (object->middleRight && object->topRight) {
		object->pushesLeftWall = true;
		return true;
	}
	if (object->middleRight && object->btmRight) {
		object->pushesLeftWall = true;
		return true;
	}
	object->pushesRightWall = false;
	return false;

}

bool Game::checkLeftSide(GameObject * object, int xOffset, int yOffset)
{
	object->topLeft = isSolid(object->collisionRect.top + yOffset, object->collisionRect.left + xOffset);
	object->btmLeft = isSolid(object->collisionRect.bottom + yOffset, object->collisionRect.left + xOffset);
	object->middleLeft = isSolid(object->collisionRect.bottom - (object->getHeight() / 2) + yOffset, object->collisionRect.left + xOffset);
	if (object->topLeft && object->btmLeft) {
		object->pushesLeftWall = true;

		return true;
	}
	if (object->middleLeft && object->topLeft) {
		object->pushesLeftWall = true;
		return true;
	}
	if (object->middleLeft && object->btmLeft) {
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
				tiles[row][collumn] = new Platform(collumn, row, D3DXVECTOR2(1.0f, 1.0f), 1, TILEWIDTH, TILEHEIGHT, tileMap[row][collumn], numOfTiles);
				tiles[row][collumn]->initialize(game->graphics->device3d, "sprite\\TileMap.png", 288, 528, 11, 6, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f);
				numOfTiles++;
			}
		}

	}


}

void Game::assignInput(GameEngine *game)
{
	if (object[0] != NULL) {
		object[0]->upArrowKey = game->input->upArrowKey;
		object[0]->rightArrowKey = game->input->rightArrowKey;
		object[0]->downArrowKey = game->input->downArrowKey;
		object[0]->leftArrowKey = game->input->leftArrowKey;
		object[0]->jumpKey = game->input->jumpKey;
		if (game->input->upArrowKey == true) {
			game->network->sendbuf[1] = '1';
			game->network->sendbuf[0] = 'Y';
		}
		if (game->input->rightArrowKey == true) {
			game->network->sendbuf[1] = '2';
			game->network->sendbuf[0] = 'Y';
		}
		if (game->input->downArrowKey == true) {
			game->network->sendbuf[1] = '3';
			game->network->sendbuf[0] = 'Y';
		}
		if (game->input->leftArrowKey == true) {
			game->network->sendbuf[1] = '4';
			game->network->sendbuf[0] = 'Y';
		}
		if (game->input->jumpKey == true) {
			if (object[0]->onGround)
			{
		
				game->sound->playJumpSound();
			}
			game->network->sendbuf[2] = '5';
			game->network->sendbuf[0] = 'Y';
		}
		if(game->network->counter >= 60){
		game->network->sendbuf += std::to_string(object[0]->getObjectPos().x) + std::to_string(object[0]->getObjectPos().y);
		game->network->sendbuf[0] = 'Y';
		game->network->counter = 0;
		}
	}



}
void Game::multiplayer(GameEngine * game)
{
	if (object[1] != NULL) {
		object[1]->upArrowKey = false;
		object[1]->rightArrowKey = false;
		object[1]->downArrowKey = false;
		object[1]->leftArrowKey = false;
		object[1]->jumpKey = false;

		if (game->network->recvbuf[1] == '1') {
			object[1]->upArrowKey = true;
			game->network->recvbuf[1] = 0;

		}
		if (game->network->recvbuf[1] == '2') {
			object[1]->rightArrowKey = true;
			game->network->recvbuf[1] = 0;


		}
		if (game->network->recvbuf[1] == '3') {
			object[1]->downArrowKey = true;
			game->network->recvbuf[1] = 0;

		}
		if (game->network->recvbuf[1] == '4') {
			object[1]->leftArrowKey = true;
			game->network->recvbuf[1] = 0;

		}
		if (game->network->recvbuf[2] == '5') {
			object[1]->jumpKey = true;
			game->network->recvbuf[2] = 0;

		}
	}
}


bool Game::contains(Node & node, std::vector<Node> vecNode)
{
	for (int i = 0; i < vecNode.size(); i++)
		if (node.row == vecNode[i].row && node.col == vecNode[i].col) {
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

void Game::retracePath(GameObject * object, Node & end, float xOffset, float yOffset)
{
	object->path.clear();
	object->path.shrink_to_fit();
	Node trace = end;
	int i = 0;

	while (trace.id != start.id) {

		object->path.push_back(trace);
		lines[i] = { (float)(((object->path.back().col *TILEHEIGHT) - xOffset) + TILEHEIGHT / 2),(float)((object->path.back().row *TILEHEIGHT) - yOffset + TILEHEIGHT / 2) };
		trace = *trace.parent;
		std::cout << object->path.back().col << "       " << object->path.back().row << std::endl;


		i++;
	}

	//	std::cout << path.back().parent->col << "       " << path.back().parent->row << std::endl;
		//lines[path.size()] = { (float)(path.back().col *TILEHEIGHT),(float)(path.back().col *TILEHEIGHT) };

}


void Game::initializeAstar()
{

	for (int i = 0; i < (GAME_HEIGHT / TILEHEIGHT)*(GAME_WIDTH / TILEWIDTH); i++) {
		blocks[i] = new Node();
	}
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
}


int Game::findPath(GameObject * object, D3DXVECTOR2 end, float xOffset, float yOffset, float spritesWidth, float spritesHeight)
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

	openList.clear();
	closeList.clear();
	neighbour.clear();

	openList.shrink_to_fit();
	closeList.shrink_to_fit();
	neighbour.shrink_to_fit();

	nodeId = 1;
	if (object->prevCol != target.col && object->prevRow != target.row) {
		start.col = object->getCollumn();
		start.row = object->getRow();
		target.row = (end.y + (spritesHeight / 2)) / TILEWIDTH;
		target.col = (end.x + (spritesWidth / 2)) / TILEHEIGHT;
		object->prevCol = target.col;					//this stores the previous so that if its the same i dont need to path find again( should not use this if there are moving platforms in my game)
		object->prevRow = target.row;
		object->path.clear();
		object->path.shrink_to_fit();
		if (tileMap[target.row][target.col] > 0) {
			std::cout << "path not found";
			object->prevCol = 0;
			object->prevRow = 0;
			return 0;
		}
		start.gCost = 0;
		start.hCost = 0;
		start.id = blocks[nodeId]->id = nodeId;
		blocks[nodeId]->col = start.col;
		blocks[nodeId]->row = start.row;
		blocks[nodeId]->walkability = true;
		start.walkability = true;
		std::cout << " START : " << start.row << " ," << start.col << "  " << std::endl;
		std::cout << " END : " << target.row << " ," << target.col << "  " << std::endl;
		openList.push_back(start);				// step 1. add start point to open list
		//openList.insert(*start);
		while (openList.size() > 0) {
			currentNode = openList[0];

			for (int i = 1; i < openList.size(); i++)
				if (openList[i].getFCost() < currentNode.getFCost() || (openList[i].getFCost() == currentNode.getFCost() && openList[i].hCost < currentNode.hCost)) {
					//if (openList[i].getFCost() <= currentNode.getFCost()) {
					currentNode = openList[i];
				}
			if (contains(currentNode, openList)) {			//check if currentNode is inside and if it is inside i need to know what is his element number in order for me to delete
				openList.erase(openList.begin() + currentNode.elementNo);
			}
			//	openList.

			closeList.push_back(currentNode);
			//blocks.push_back(currentNode);
			if (currentNode.row == target.row && currentNode.col == target.col) {

				retracePath(object, currentNode, xOffset, yOffset);
				openList.clear();
				closeList.clear();
				neighbour.clear();
				return 1;
			}

			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (x == 0 && y == 0)
						continue;
					//arrayRow += (i / (GAME_WIDTH / TILEWIDTH));
					//arrayCol = i % (GAME_WIDTH / TILEWIDTH);

					if (currentNode.row + y > 0 || currentNode.row + y < TILEROW || currentNode.col + x < TILECOLUMN || currentNode.col + x >0) {
						if (tileMap[currentNode.row + y][currentNode.col + x] == 0) {
							neighbour.push_back(Node());
							neighbour.back().walkability = true;
							neighbour.back().col = currentNode.col + x;
							neighbour.back().row = currentNode.row + y;
							//neighbour.back().parent = &closeList.back();//&blocks[((currentNode.row + x)*TILECOLUMN)+];
							//neighbour.back().id = currentNode.id;

						}
					}
				}
			}

			for (auto& neighbour : neighbour) {
				if (contains(neighbour, closeList))
					continue;

				movementCostToNeighbour = currentNode.gCost + getDistance(currentNode, neighbour);

				if (movementCostToNeighbour < neighbour.gCost || !contains(neighbour, openList)) 				// if neighbour not inside openlist
				{
					nodeId++;
					neighbour.id = nodeId;
					neighbour.gCost = blocks[neighbour.id]->gCost = movementCostToNeighbour;
					neighbour.hCost = blocks[neighbour.id]->hCost = getDistance(neighbour, target);
					neighbour.parentId = blocks[neighbour.id]->parentId = closeList.back().id;
					neighbour.parent = blocks[neighbour.parentId];
					blocks[neighbour.id]->parent = blocks[neighbour.parentId];
					*blocks[nodeId] = neighbour;
					if (!contains(neighbour, openList)) {
						openList.push_back(neighbour);

					}
					/*if (!(std::find(openList.begin(), openList.end(), neighbour) != openList.end())) {
						openList.push_back(neighbour);
					}*/

				}
			}
			neighbour.clear();




		}
	}
	//nodeId = 0;
	std::cout << "path is the same";
	openList.clear();
	closeList.clear();
	neighbour.clear();




	return 0;
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


Game::Game()
{

	initialize = false;

}


Game::~Game()
{


}
