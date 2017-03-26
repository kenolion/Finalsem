#include "LevelPlayerWins.h"
#include "LevelMainMenu.h"
#include "FlappyBird.h"
#include "GameEngine.h"

LevelPlayerWins LevelPlayerWins::winState;
bool LevelPlayerWins::initializeGame(HWND hwnd, GameEngine * game)
{

	game->sound->playPlayerWinMusic();
	game->sound->channel->setVolume(0.0f);
	//======================================================= Create your Game Objects Here =======================================================
	backgroundImage = new Pictures(0.0f, 0.0f, D3DXVECTOR2(1.0f, 1.0f),1); //x, y, scaling, animation, speed,mass
	if (!backgroundImage->initialize(game->graphics->device3d, "sprite\\backgroundImage.png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the backgroundImage", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	youWinTextLogo = new Pictures(200, 100, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!youWinTextLogo->initialize(game->graphics->device3d, "sprite\\youWinLogo.png", 891, 179, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the game logo image", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	returnToMainMenuButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, " Main Menu", 10, 255, 155, 0, game->graphics->font); //X to print, Y to print position and scaling.
	returnToMainMenuButton->setX(50);
	returnToMainMenuButton->setY(600);

	if (!returnToMainMenuButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the start button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	childrenPointer1 = dynamic_cast<Button*>(returnToMainMenuButton);

	//---------------------------------------------------------------------------------------------------------------------------------------------

	quitButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Exit Game", 10, 255, 155, 0, game->graphics->font);
	quitButton->setX(950);
	quitButton->setY(600);

	if (!quitButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the quit button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	childrenPointer2 = dynamic_cast<Button*>(quitButton);
	game->state = GameStates::LEVELPLAYERWIN;			//<---- important to set to its current state
	game->exit = false;
	return initialize = true;


}

void LevelPlayerWins::update(int gameTime, GameEngine * game)
{

	game->cursor->posVector = { (float)mouseX,(float)mouseY };
	game->cursor->update(gameTime, game->camera->getXOffset(), game->camera->getYOffset()); //Update cursor according to mouseX and mouseY

	if (childrenPointer1->onHover(mouseX, mouseY))
	{
		if (childrenPointer1->isClicked(game->input->leftClickDown))
		{
			//returnToMainMenu
			game->state = GameStates::MENU;
			game->sound->pausePlayerWinMusic();
		}
		returnToMainMenuButton->update(gameTime, game->camera->getXOffset(), game->camera->getYOffset());
	}
	else {
		returnToMainMenuButton->setFrame(1);
	}

	if (childrenPointer2->onHover(mouseX, mouseY))
	{
		if (childrenPointer2->isClicked(game->input->leftClickDown))
		{
			//quitgame
			game->state = GameStates::EXITPROGRAM;
			game->sound->fmodSystem->release();
		}
		quitButton->update(gameTime, game->camera->getXOffset(), game->camera->getYOffset());
	}
	else {
		quitButton->setFrame(1);
	}
}

void LevelPlayerWins::collisions(GameEngine * game)
{
	//Collision should not update players position
	//	for (int i = 0; i<GOBJECTNUML1; i++) {
	//		object[i]->posVector = object[i]->getObjectPos();
	//	}


}

void LevelPlayerWins::handleEvents(GameEngine * game)
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

void LevelPlayerWins::draw(GameEngine * game)
{
	game->graphics->clear(D3DCOLOR_XRGB(255, 204, 255)); //255 204 255 = Pink
	game->graphics->begin();

	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//======================================================= Draw your Objects in Here =======================================================

	backgroundImage->draw(game);
	youWinTextLogo->draw(game);

	returnToMainMenuButton->draw(game);
	quitButton->draw(game);

	//==============================================================================================================================================
	game->cursor->draw(game);
	game->sprite->End();

	game->graphics->end();
	game->graphics->present();
}

void LevelPlayerWins::deleteAll()
{
	dltPtr(youWinTextLogo);
	dltPtr(backgroundImage);
	dltPtr(returnToMainMenuButton);
	dltPtr(quitButton);
}


LevelPlayerWins::~LevelPlayerWins()
{
}

