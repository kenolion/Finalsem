#include "LevelYouFail.h"
#include "LevelMainMenu.h"
#include "FlappyBird.h"
#include "GameEngine.h"
#include "Button.h"
#include "Pictures.h"


LevelYouFail LevelYouFail::levelfail;
bool LevelYouFail::initializeGame(HWND hwnd, GameEngine * game)
{
	//i think its my return to main menu button

	game->sound->playFailMusic();
	game->sound->channel->setVolume(0.25f);
	//======================================================= Create your Game Objects Here =======================================================
	gameOverText = new Pictures(320, 100, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!gameOverText->initialize(game->graphics->device3d, "sprite\\GAMEOVER.png", 620, 208, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the game logo image", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	deadTallGuyPic = new Pictures(380, 350, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!deadTallGuyPic->initialize(game->graphics->device3d, "sprite\\deadTallguy.png", 81, 45, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the dead madafaka", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	deadFatGuyPic = new Pictures(770, 350, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!deadFatGuyPic->initialize(game->graphics->device3d, "sprite\\deadFatGuy.png", 87, 75, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the dead fat madafaka", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------

	returnToMainMenuButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, " Main Menu", 10, 255, 155, 0, game->graphics->font, GameStates::MENU, ButtonType::NORMAL); //X to print, Y to print position and scaling.
	returnToMainMenuButton->setPosition(50, 600);

	if (!returnToMainMenuButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the start button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------

	quitButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Exit Game", 10, 255, 155, 0, game->graphics->font, GameStates::EXITPROGRAM, ButtonType::NORMAL);
	quitButton->setPosition(950, 600);
	if (!quitButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the quit button", NULL, NULL);
		return initialize = false; //If false program wont run
	}

	game->state = GameStates::LEVELYouFail;			//<---- important to set to its current state
	game->exit = false;
	return initialize = true;


}

void LevelYouFail::update(int gameTime, GameEngine * game)
{

	game->cursor->update(gameTime, game); //Update cursor according to mouseX and mouseY
	gameOverText->update(gameTime, game);
	returnToMainMenuButton->update(gameTime, game);
	quitButton->update(gameTime, game);

}

void LevelYouFail::collisions(GameEngine * game, int gameTime)
{


}

void LevelYouFail::handleEvents(GameEngine * game)
{
	switch (game->state) {
	case GameStates::MENU:
		game->popState();
		break;
	case GameStates::EXITPROGRAM:
		game->exit = true;
		break;
	}

}

void LevelYouFail::draw(GameEngine * game)
{

	game->graphics->clear(D3DCOLOR_XRGB(0, 0, 0));
	//game->graphics->clear(D3DCOLOR_XRGB(255, 204, 255)); //255 204 255 = Pink
	game->graphics->begin();

	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//======================================================= Draw your Objects in Here =======================================================

	returnToMainMenuButton->draw(game);
	quitButton->draw(game);
	gameOverText->draw(game);
	deadTallGuyPic->draw(game);
	deadFatGuyPic->draw(game);
	//==============================================================================================================================================
	game->cursor->draw(game);
	game->sprite->End();

	game->graphics->end();
	game->graphics->present();
}

void LevelYouFail::deleteAll()
{
	dltPtr(gameOverText);
	dltPtr(returnToMainMenuButton);
	dltPtr(quitButton);
	dltPtr(deadTallGuyPic);
	dltPtr(deadFatGuyPic);

}


LevelYouFail::LevelYouFail()
{
}

LevelYouFail::~LevelYouFail()
{
}

