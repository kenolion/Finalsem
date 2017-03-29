#include "Game.h"
#include "GameEngine.h"
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
	game->input->GetMouseLocation(mouseX, mouseY);						//Stores the converted absolute position to the Input class's mouseX and mouseY variable
	game->cursor->posVector = { (float)mouseX,(float)mouseY };			//Sets the Cursor Position to the Absolute MouseX and MouseY in the window.
	collisions(game, framesToUpdate);
	update(framesToUpdate, game);
	draw(game);// draws the games graphics


}

bool Game::isSolid(int x, int y)
{
	std::cout << tileMap[x / TILEWIDTH][y / TILEHEIGHT] << "    "<< std::endl;
	if (tileMap[x / TILEWIDTH][y / TILEHEIGHT] > 0) {
		return true;
	}
	else {
		return false;
	}
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

void Game::initializeTiles(GameEngine*game)
{
	numOfTiles = 0;
	for (int row = 0; row < TILEROW; row++) {
		for (int collumn = 0; collumn < TILECOLUMN; collumn++) {

			if (tileMap[row][collumn] > 0) {
				tiles[numOfTiles] = new Platform(collumn, row, D3DXVECTOR2(1.0f, 1.0f), 1, TILEWIDTH, TILEHEIGHT, tileMap[row][collumn]);
				tiles[numOfTiles]->initialize(game->graphics->device3d, "sprite\\TileMap.png", 288, 480, 10, 6, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f);
				numOfTiles++;
			}
		}

	}


}



