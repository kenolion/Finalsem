#include "LevelMainMenu.h"
#include "FlappyBird.h"
#include "LevelPlayerWins.h"
#include "GameEngine.h"
LevelMainMenu LevelMainMenu::mainMenuState;

bool LevelMainMenu::initializeGame(HWND hwnd, GameEngine * game)
{

	game->sound->playMainMenuMusic();
	game->sound->channel->setVolume(0.0f);
	//======================================================= Create your Game Objects Here =======================================================
	backgroundImage = new Pictures(0.0f, 0.0f, D3DXVECTOR2(1.0f, 1.0f), 1); //x, y, scaling, animation, speed,mass
	if (!backgroundImage->initialize(game->graphics->device3d, "sprite\\backgroundimage.png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the backgroundImage", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	gameLogo = new Pictures(100,100, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!gameLogo->initialize(game->graphics->device3d, "sprite\\gameLogo.png", 1130, 97, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the game logo image", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	startButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f),30, "Start Game", 10, 255,155,0, game->graphics->font); //X to print, Y to print position and scaling.
	startButton->setX(50);
	startButton->setY(600);


	if(!startButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255,255,255),1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the start button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	quitButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Exit Game", 10, 255, 155, 0, game->graphics->font);
	quitButton->setX(950);
	quitButton->setY(600);

	if (!quitButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the quit button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	
	//---------------------------------------------------------------------------------------------------------------------------------------------
	childrenPointer = dynamic_cast<Button*>(startButton); //This makes it so that a derived class can access base class methods and variables through pointing with "childrenPointer2"
	childrenPointer2 = dynamic_cast<Button*>(quitButton); //Children class = Parent class
	game->exit = false;
	game->state = GameStates::MENU;
	return initialize = true;

}

void LevelMainMenu::update(int gameTime, GameEngine * game)
{

	game->cursor->update(gameTime,game->camera->getXOffset(), game->camera->getYOffset()); //Update cursor according to mouseX and mouseY
	//---------------------------------------------------------------------------------------------------------------------------------------------

	Button *childrenPointer = dynamic_cast<Button*>(startButton); //Children class = Parent 

	if (childrenPointer->onHover(mouseX, mouseY)) 
	{
		if (childrenPointer->isClicked(game->input->leftClickDown))
		{
			//change to level one
			game->state = GameStates::LEVEL1;
			game->sound->pauseMainMenuMusic();
			
		}
		startButton->update(gameTime, game->camera->getXOffset(), game->camera->getYOffset());
	}
	else{
		startButton->setFrame(1);
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	Button *childrenPointer2 = dynamic_cast<Button*>(quitButton); //Children class = Parent class
	
	if (childrenPointer2->onHover(mouseX, mouseY))
	{
		if (childrenPointer2->isClicked(game->input->leftClickDown))
		{
			//quit game; Game state = (something) to quit
			game->state = GameStates::EXITPROGRAM;
			game->sound->fmodSystem->release();
		}
		quitButton->update(gameTime, game->camera->getXOffset(), game->camera->getYOffset());
	}
	else {
		quitButton->setFrame(1);
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	

	
}

void LevelMainMenu::collisions(GameEngine * game, int gameTime)
{
	//Collision should not update players position
//	for (int i = 0; i<GOBJECTNUML1; i++) {
//		object[i]->posVector = object[i]->getObjectPos();
//	}

}

void LevelMainMenu::handleEvents(GameEngine *game)
{
	switch (game->state) {
	case GameStates::EXITPROGRAM:
		game->exit = true;
		break;
	case GameStates::LEVEL1:
		game->pushState(FlappyBird::getInstance(),hwnd);
		break;
	}

}

void LevelMainMenu::draw(GameEngine * game)
{
	game->graphics->clear(D3DCOLOR_XRGB(0,0,0)); //255 204 255 = Pink
	game->graphics->begin();

	game->graphics->createLine();
	game->graphics->lineBegin();

	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//======================================================= Draw your Objects in Here =======================================================

	backgroundImage->draw(game);
	gameLogo->draw(game);
	startButton->draw(game);
	quitButton->draw(game);
	

	//==============================================================================================================================================
	game->cursor->draw(game);
	game->sprite->End();

	game->graphics->lineEnd();

	game->graphics->end();
	game->graphics->present();
}

void LevelMainMenu::deleteAll()
{

	dltPtr(startButton);
	dltPtr(quitButton);
	dltPtr(backgroundImage);
	dltPtr(gameLogo);
	
		
}		


LevelMainMenu::LevelMainMenu()
{
}


LevelMainMenu::~LevelMainMenu()
{
}

