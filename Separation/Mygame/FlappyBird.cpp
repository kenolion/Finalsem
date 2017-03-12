#include "FlappyBird.h"
#include "LevelMainMenu.h"
#include "GameEngine.h"
#include "LevelPlayerWins.h"
FlappyBird FlappyBird::level1State;

bool FlappyBird::initializeGame(HWND hwnd, GameEngine * game)
{
	game->sound->playMainMenuMusic();
	game->sound->channel->setVolume(0.0f);
	object[1] = new Player(50.0f, (float)(GAME_HEIGHT / 2), D3DXVECTOR2(1.0f, 1.0f), 10, 2.0f, 5);
	object[0] = new Pictures(0.0f, 0.0f, D3DXVECTOR2(1.0f, 1.0f));
	object[2] = new Platform(500.0f, 600.0f, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!object[0]->initialize(game->graphics->device3d, "sprite\\skybackground.png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	if (!object[1]->initialize(game->graphics->device3d, "sprite\\ben.png", 128, 192, 4, 4, true, D3DCOLOR_XRGB(0, 0, 0), 0.80f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!object[2]->initialize(game->graphics->device3d, "sprite\\smalldick.png", 224, 69, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------
	menuButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Main Menu", 10, 255, 155, 0, game->graphics->font);
	menuButton->setX(600);
	menuButton->setY(600);

	if (!menuButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the menuButton", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	childrenPointer = dynamic_cast<Button*>(menuButton);
	//---------------------------------------------------------------------------------------------------------------------------------------------

	gravity = { 0,GRAVITY };
	object[1]->setState(3);
	game->exit = false;
	game->state = GameStates::LEVEL1;
	return initialize = true;
}

void FlappyBird::update(int gameTime, GameEngine * game)
{
	if (childrenPointer->onHover(mouseX, mouseY))
	{
		if (childrenPointer->isClicked(game->input->leftClickDown))
		{
			game->state = GameStates::MENU;
			game->sound->fmodSystem->release();
		}
		menuButton->update(gameTime);
	}
	else {
		menuButton->setFrame(1);
	}

	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		object[i]->update(gameTime);

	}
	menuButton->update(gameTime);
	game->cursor->update(gameTime);
}

void FlappyBird::draw(GameEngine * game)
{
	game->graphics->clear(D3DCOLOR_XRGB(0, 100, 100));
	game->graphics->begin();
	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);


	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		object[i]->draw(game);
	}
	menuButton->draw(game);

	game->cursor->setMatrix(D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, D3DXVECTOR2(GAME_WIDTH / 2, 25), game);		//Set this to draw my font
	game->graphics->drawfont("Score : ", timer * 10, 13, 500, 50, game->sprite, D3DCOLOR_XRGB(255, 0, 0), 30);			// last parameter depends on the size of your font
	game->cursor->draw(game);
	game->sprite->End();
	game->graphics->end();
	game->graphics->present();
}

void FlappyBird::collisions(GameEngine * game)
{

	object[1]->forceVector = { 0,0 };
	
}

void FlappyBird::deleteAll()
{
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		dltPtr(object[i]);
	}
	dltPtr(menuButton);
}

void FlappyBird::handleEvents(GameEngine * game)
{
	switch (game->state) {
	case GameStates::LEVELPLAYERWIN:
		game->changeState(LevelPlayerWins::getInstance(), hwnd);
		break;
	case GameStates::MENU:
		game->popState();
		break;
	}

}

FlappyBird::FlappyBird()
{

}


FlappyBird::~FlappyBird()
{
}
