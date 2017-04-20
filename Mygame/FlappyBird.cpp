#include "FlappyBird.h"
#include "LevelMainMenu.h"
#include "GameEngine.h"
#include "LevelPlayerWins.h"
#include "Button.h"
#include "Pictures.h"
#include "Player.h"
#include "InteractableObjects.h"
#include "Platform.h"
#include "LevelTwo.h"
#include "Enemy.h"
FlappyBird FlappyBird::level1State;

bool FlappyBird::initializeGame(HWND hwnd, GameEngine * game)
{

	mapName = "TileMap.txt";
	game->sound->playLevel1Music();
	game->sound->channel->setVolume(0.25f);


	object[1] = new Player(200, 248, D3DXVECTOR2(1.0f, 1.0f), 10, 5, 2);									//last parameter is player type 2 is fatguy
	object[0] = new Player(16 * TILEWIDTH, 13 * TILEHEIGHT, D3DXVECTOR2(1.0f, 1.0f), 10, 5, 1);				//animationspeed no longer set here! it is now set at animation manager because some animations might have diferent speed
	enemy[0] = new Enemy(26 * TILEWIDTH, 4 * TILEHEIGHT, { 1.0f,1.0f }, 10, 1);
	parallaxBG1 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	parallaxBG2 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	parallaxBG3 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);

	dungeonKey = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	dungeonDoor = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);

	if (!dungeonKey->initialize(game->graphics->device3d, "sprite\\dungeonkey.png", 49, 49, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	dungeonKey->setPosition(16 * TILEWIDTH, 5 * TILEHEIGHT);

	if (!dungeonDoor->initialize(game->graphics->device3d, "sprite\\dungeondoor.png", 49, 49, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	dungeonDoor->setPosition(30 * TILEWIDTH, 14 * TILEHEIGHT);


	if (!object[0]->initialize(game->graphics->device3d, "sprite\\tallguy.png", 1024, 512, 5, 10, true, D3DCOLOR_XRGB(0, 0, 0), 0.97f)) {			//512 256 5 10
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);				//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!object[1]->initialize(game->graphics->device3d, "sprite\\fatguysmall.png", 512, 512, 6,8, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	if (!enemy[0]->initialize(game->graphics->device3d, "sprite\\batfull.png", 256, 62, 8, 2, true, D3DCOLOR_XRGB(0, 0, 0), 0.90f)) {
		MessageBox(NULL, "There was an issue creating the enemy sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
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
	menuButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Main Menu", 10, 255, 155, 0, game->graphics->font, GameStates::MENU, ButtonType::NORMAL);
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
	initializeAstar();
	//findPath(object[1]->getObjectPos(),object[0]->getObjectPos());// D3DXVECTOR2(200,552)
	game->exit = false;
	game->state = GameStates::LEVEL1;
	if (clientType == 2) {
		tempObject = object[1];
		object[1] = object[0];
		object[0] = tempObject;
	}
	keyObtained = false;
	counter = 0;
	return initialize = true;
}


void FlappyBird::collisions(GameEngine * game, int gameTime)
{
	//game->setDrawingPoint(0, 0);


	object[1]->physics(game->input, gameTime);
	object[0]->physics(game->input, gameTime);
	for (int i = 0; i < gameTime; i++) {
		object[0]->moveXdirection();
		if (checkRightSide(object[0], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[0]->handleXAxisCollision();
		}
		if (checkLeftSide(object[0], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[0]->handleXAxisCollision();
		}
		object[0]->moveYdirection();
		if (checkGround(object[0], game->camera->getXOffset(), game->camera->getYOffset())) {			// to do split x and y and calculate overlap.
			object[0]->handleYAxisCollision();
		}
		if (checkCeiling(object[0], game->camera->getXOffset(), game->camera->getYOffset())) {
			object[0]->handleYAxisCollision();
		}


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


		for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
			object[0]->collideWith(enemy[0]);
			if (enemy[0]->getDistance(object[0]) < enemy[0]->detectionRadius) {//calculate distance and current object
																			   //enemy[0]->objectInRadius = true; // player is in the radius
				if (counter >= 30) {
					findPath(enemy[0], object[0]->getObjectPos(), game->camera->getXOffset(), game->camera->getYOffset(), object[0]->getWidth(), object[0]->getHeight());
					counter = 0;	
				}
				enemy[0]->moveXdirection();
				enemy[0]->moveYdirection();
			}
			if (dungeonKey->collideWith(object[i]))
			{
				keyObtained = true;
				dungeonKey->setStatus(ObjectStatus::Dead);

			}
			if (dungeonDoor->collideWith(object[i]))
			{
				if (keyObtained == true);
				{
					game->state = GameStates::LEVEL2;
				}
				//win the game;
			}
		}
		game->network->counter++;
		counter++;
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
	enemy[0]->update(gameTime, game);
	parallaxBG1->update(gameTime, game);
	parallaxBG2->update(gameTime, game);
	parallaxBG3->update(gameTime, game);
	menuButton->update(gameTime, game);

	dungeonKey->update(gameTime, game);
	dungeonDoor->update(gameTime, game);

	game->cursor->update(gameTime, game);


	menuButton->update(gameTime, game);
	game->cursor->update(gameTime, game);
	game->camera->centerOnObject(object[0]);
}

void FlappyBird::draw(GameEngine * game)
{

	game->graphics->clear(D3DCOLOR_XRGB(255, 255, 255));
	//game->graphics->clear(D3DCOLOR_XRGB(0, 100, 100), object[1]->collisionRect);
	//game->graphics->clear(D3DCOLOR_XRGB(100, 0, 0), object[1]->legRect);

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
	dungeonDoor->draw(game);

	dungeonKey->draw(game);
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {

		object[i]->draw(game);
	}
	enemy[0]->draw(game);
	menuButton->draw(game);

	game->cursor->setMatrix(D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, D3DXVECTOR2(GAME_WIDTH / 2, 25), game);		//Set this to draw my font
	game->graphics->drawfont("Score : ", timer * 10, 13, 500, 50, game->sprite, D3DCOLOR_XRGB(255, 0, 0), 30);			// last parameter depends on the size of your font
	game->cursor->draw(game);

	game->sprite->End();
	game->graphics->lineBegin();
	game->graphics->drawLine(lines, enemy[0]->path.size(), 255, 0, 0);
	game->graphics->drawLine(object[0]->CollisionBox, 5, 255, 0, 0);
	game->graphics->drawLine(enemy[0]->CollisionBox, 5, 255, 0, 0);
	game->graphics->lineEnd();

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
	
	dltPtr(menuButton);
	dltPtr(parallaxBG1);
	dltPtr(parallaxBG2);
	dltPtr(parallaxBG3);
	dltPtr(dungeonKey);
	dltPtr(dungeonDoor);
	dltPtr(enemy[0]);

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
	case GameStates::LEVEL2:
		game->sound->pauseLevel1Music();
		game->changeState(LevelTwo::getInstance(), hwnd);
	}

}


FlappyBird::FlappyBird()
{

}


FlappyBird::~FlappyBird()
{

}
