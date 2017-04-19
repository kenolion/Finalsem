#include "FlappyBird.h"
#include "LevelMainMenu.h"
#include "GameEngine.h"
#include "LevelPlayerWins.h"
#include "Button.h"
#include "Pictures.h"
#include "Player.h"
#include "Platform.h"
FlappyBird FlappyBird::level1State;

bool FlappyBird::initializeGame(HWND hwnd, GameEngine * game)
{

	mapName = "TileMap.txt";
	game->sound->playMainMenuMusic();
	game->sound->channel->setVolume(0.0f);


	object[2] = new Player(200,200, D3DXVECTOR2(1.0f, 1.0f), 10, 5);
	object[1] = new Player(GAME_WIDTH / 2, GAME_HEIGHT / 2, D3DXVECTOR2(1.0f, 1.0f), 10, 5);
	object[0] = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);						//(x,y,Scaling)
	parallaxBG1 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	parallaxBG2 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	parallaxBG3 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);

	if (!object[0]->initialize(game->graphics->device3d, "sprite\\skybackground.png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!object[1]->initialize(game->graphics->device3d, "sprite\\tallguyfull.png", 512, 256, 5,10, true, D3DCOLOR_XRGB(0, 0, 0), 0.95f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);				//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!object[2]->initialize(game->graphics->device3d, "sprite\\ben.png", 128, 192, 4, 4, true, D3DCOLOR_XRGB(0, 0, 0), 0.90f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!parallaxBG1->initialize(game->graphics->device3d, "sprite\\parallax 1 (7).png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the bg", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!parallaxBG2->initialize(game->graphics->device3d, "sprite\\parallax 1 (2).png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the bg", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!parallaxBG3->initialize(game->graphics->device3d, "sprite\\parallax 1 (3).png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the bg", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}



	//---------------------------------------------------------------------------------------------------------------------------------------------
	menuButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Main Menu", 10, 255, 155, 0, game->graphics->font,GameStates::MENU, ButtonType::NORMAL);
	menuButton->setPosition(600, 0);

	if (!menuButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the menuButton", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	if (!loadLevel()) {
		return initialize = false;
	}
	initializeTiles(game);

	gravity = { 0,GRAVITY };
	object[1]->setState(3);
	//initializeAstar();
	//findPath(object[1]->getObjectPos(), D3DXVECTOR2(200,600));
	game->exit = false;
	game->state = GameStates::LEVEL1;
	return initialize = true;
}


void FlappyBird::collisions(GameEngine * game, int gameTime)
{
	//game->setDrawingPoint(0, 0);


	object[1]->physics(game->input, gameTime);
	for (int i = 0; i < gameTime; i++) {
		object[1]->moveYdirection();
		if (checkGround(object[1], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[1]->handleYAxisCollision();
		}
		if (checkCeiling(object[1], game->camera->getXOffset(), game->camera->getYOffset())) {
			object[1]->handleYAxisCollision();
		}
		object[1]->moveXdirection();
		if (checkRightSide(object[1], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[1]->handleXAxisCollision();
		}
		if (checkLeftSide(object[1], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[1]->handleXAxisCollision();
		}

	}
}


void FlappyBird::update(int gameTime, GameEngine * game)
{


	for (int row = 0; row < TILEROW; row++) {
		for (int col = 0; col < TILECOLUMN; col++) {
			if (tiles[row][col] != NULL)
				tiles[row][col]->update(gameTime, game);
		}

	}
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		object[i]->update(gameTime, game);

	}
	parallaxBG1->update(gameTime, game);
	parallaxBG2->update(gameTime, game);
	parallaxBG3->update(gameTime, game);
	menuButton->update(gameTime, game);
	game->cursor->update(gameTime, game);


	menuButton->update(gameTime, game);
	game->cursor->update(gameTime, game);
	game->camera->centerOnObject(object[1]);
}

void FlappyBird::draw(GameEngine * game)
{
	
	game->graphics->clear(D3DCOLOR_XRGB(255, 255, 255));
	game->graphics->clear(D3DCOLOR_XRGB(0, 100, 100), object[1]->collisionRect);
	game->graphics->clear(D3DCOLOR_XRGB(100, 0, 0), object[1]->legRect);
	game->graphics->begin();
	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	parallaxBG1->draw(game);
	parallaxBG2->draw(game);
	parallaxBG3->draw(game);
	for (int row = 0; row < TILEROW; row++) {
		for (int col = 0; col < TILECOLUMN; col++) {
			if (tiles[row][col] != NULL)
				tiles[row][col]->draw(game);
		}



	}

	for (int i = 1; i < FLAPPYBIRDOBJECTS; i++) {

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

void FlappyBird::deleteAll()
{

	for (int row = 0; row < TILEROW; row++) {
		for (int col = 0; col < TILECOLUMN; col++) {
			if (tiles[row][col] != NULL)
				dltPtr(tiles[row][col]);
		}

	}
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		dltPtr(object[i]);
	}
	dltPtr(menuButton);
	dltPtr(parallaxBG1);
	dltPtr(parallaxBG2);
	dltPtr(parallaxBG3);
	//freeAStar();

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

void FlappyBird::multiplayer(GameEngine * game)
{
	if (game->network->recvbuf == "left") {
		object[2]->setPosition(object[2]->getObjectPos().x + 1, object[2]->getObjectPos().y);
		*game->network->recvbuf = 0;
	}
	if (game->network->recvbuf == "right") {
		*game->network->recvbuf = 0;
	}
	if (game->network->recvbuf == "jump") {
		*game->network->recvbuf = 0;
	}
	if (game->network->recvbuf == "up") {
		*game->network->recvbuf = 0;
	}

}


FlappyBird::FlappyBird()
{

}


FlappyBird::~FlappyBird()
{

}
