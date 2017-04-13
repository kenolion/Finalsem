#include "Game.h"
#include "GameEngine.h"
#include "Platform.h"
Game::Game()
{

	initialize = false;

}


Game::~Game()
{
}



void Game::run(GameEngine * game)	// This function is called repeatedly by main message loop
{
	framesToUpdate = game->gameTime->update();
	game->input->getInput();												//A function that detects for input 
	game->input->ReadMouse();												//Read the mouse Device
	game->input->convertRelativeToAbsolute();								//Converts Relative X and Y mouse position to Absolute position
	game->cursor->setPosition(game->input->GetMouseLocation().x, game->input->GetMouseLocation().y);		//Sets the Cursor Position to the Absolute MouseX and MouseY in the window.
	//std::cout << mouseX << "     " << mouseY << "      " << std::endl;
	multiplayer(game);
	collisions(game, framesToUpdate);
	update(framesToUpdate, game);
	draw(game);// draws the games graphics


}

void Game::multiplayer(GameEngine * game )
{
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
	if (tileMap[(int)ceil((x / TILEWIDTH))][(int)(ceil(y / TILEHEIGHT))] > 0) {

		return true;
	}
	
	return false;
}



bool Game::checkGround(GameObject * object, int xOffset, int yOffset)
{
	if (isSolid(object->collisionRect.bottom , object->collisionRect.left + xOffset)) {
		if (isSolid(object->collisionRect.bottom, object->collisionRect.right + xOffset)) {
			object->row = (object->collisionRect.bottom ) / TILEWIDTH;
			object->setOnGround(true);
			return true;
		}
	}
	object->setOnGround(false);
	return false;

}

bool Game::checkRightSide(GameObject * object, int xOffset, int yOffset)
{
	if (isSolid(object->collisionRect.top, object->collisionRect.right + xOffset)) {
		if (isSolid(object->collisionRect.bottom, object->collisionRect.right + xOffset)) {
			object->pushesRightWall = true;

			return true;
		}
	}
	object->pushesRightWall = false;
	return false;

}

bool Game::checkLeftSide(GameObject * object, int xOffset, int yOffset)
{
	if (isSolid(object->collisionRect.top, object->collisionRect.left + xOffset)) {
		if (isSolid(object->collisionRect.bottom, object->collisionRect.left + xOffset)) {
			object->pushesLeftWall = true;

			return true;
		}
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
				tiles[numOfTiles] = new Platform(collumn, row, D3DXVECTOR2(1.0f, 1.0f), 1, TILEWIDTH, TILEHEIGHT, tileMap[row][collumn]);
				tiles[numOfTiles]->initialize(game->graphics->device3d, "sprite\\TileMap.png", 288, 528, 11, 6, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f);
				numOfTiles++;
			}
		}

	}


}



