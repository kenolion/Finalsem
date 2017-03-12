#include "Game.h"
#include "GameStateManager.h"
Game::Game()
{

	initialize = false;
	
}


Game::~Game()
{
}



void Game::run(GameStateManager * game)	// This function is called repeatedly by main message loop
{
	framesToUpdate = game->gameTime->update();

	game->input->getInput();												//A function that detects for input 
	game->input->ReadMouse();												//Read the mouse Device
	game->input->convertRelativeToAbsolute();								//Converts Relative X and Y mouse position to Absolute position
	game->input->GetMouseLocation(mouseX, mouseY);						//Stores the converted absolute position to the Input class's mouseX and mouseY variable
	game->cursor->posVector = { (float)mouseX,(float)mouseY };			//Sets the Cursor Position to the Absolute MouseX and MouseY in the window.
	
	collisions(game);
	update(framesToUpdate,game);
	draw(game);// draws the games graphics


}

