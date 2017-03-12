#include "FlappyBird.h"
#include "LevelMainMenu.h"
#include "GameStateManager.h"
#include "LevelPlayerWins.h"
FlappyBird FlappyBird::level1State;

bool FlappyBird::initializeGame(HWND hwnd, GameStateManager * game)
{
	game->sound->playMainMenuMusic();
	game->sound->channel->setVolume(0.0f);
	object[1] = new Player(50.0f, (float)(GAME_HEIGHT / 2), D3DXVECTOR2(1.0f, 1.0f), 10, 2.0f, 5);
	object[0] = new Pictures(0.0f, 0.0f, D3DXVECTOR2(1.0f, 1.0f));
	if (!object[0]->initialize(game->graphics->device3d, "sprite\\skybackground.png", 1280, 720, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	if (!object[1]->initialize(game->graphics->device3d, "sprite\\ben.png", 128, 192, 4, 4, true, D3DCOLOR_XRGB(0, 0, 0), 0.80f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	for (int i = 2; i < 9; i++) {
		object[i] = new Enemy(i*189.0f, 609.0f, D3DXVECTOR2(1.0f, 2.0f), 10, -5.0f, 5);
		if (!object[i]->initialize(game->graphics->device3d, "sprite\\pipestanding.png", 46, 150, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
			MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}
	}
	for (int i = 9; i < 16; i++) {
		object[i] = new Enemy((i - 7)*189.0f, 0.0f, D3DXVECTOR2(1.0f, 1.5f), 10, -5.0f, 5);
		if (!object[i]->initialize(game->graphics->device3d, "sprite\\upsidedownPipe.png", 46, 150, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
			MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}
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
	srand(time(NULL));

	gravity = { 0,GRAVITY };
	object[1]->setState(3);
	game->exit = false;
	game->state = GameStates::LEVEL1;
	return initialize = true;
}

void FlappyBird::update(int gameTime,GameStateManager * game)
{
	randomNumber = rand() % 3 + 1;
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
	if (counter == REQFPS) {
		timer++;
		counter = 0;
	}
	for (int i = 0; i < gameTime; i++) {
		counter++;
	}
	game->cursor->update(gameTime);
}

void FlappyBird::draw(GameStateManager * game)
{
	game->graphics->clear(D3DCOLOR_XRGB(0, 100, 100));
	game->graphics->begin();
	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		object[i]->draw(game);
	}
	menuButton->draw(game);

	game->cursor->setMatrix(D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, D3DXVECTOR2(GAME_WIDTH / 2, 25),game);		//Set this to draw my font
	game->graphics->drawfont("Score : ", timer*10, 13, 500, 50, game->sprite, D3DCOLOR_XRGB(255, 0, 0), 30);			// last parameter depends on the size of your font
	game->cursor->draw(game);
	game->sprite->End();
	game->graphics->end();
	game->graphics->present();
}

void FlappyBird::collisions(GameStateManager * game)
{

	object[1]->forceVector = { 0,0 };
	if (game->input->upArrowKey && !(object[1]->jump)) {
		game->sound->playJumpSound();
		object[1]->jump = true;
		object[1]->forceVector = { 0,-115 };
		std::cout << object[1]->forceVector.y << std::endl;
		std::cout << object[1]->jumpCD << std::endl;
	}

	object[1]->setAcceleration(object[1]->forceVector / object[1]->getMass());
	object[1]->setVelocity(object[1]->getVelocity() + object[1]->getAcceleration());
	if (object[1]->jumpCD >= 60 && game->input->upArrowKey) {
		object[1]->jump = false;
		object[1]->jumpCD = 0;
	}
	else {

		object[1]->setVelocity(D3DXVECTOR2(0, object[1]->getVelocityY()) + gravity);
	}
	
		for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
			if (i == 1)i++;
			object[i]->setVelocity(D3DXVECTOR2(object[i]->getSpeed(), (1.15*sin(object[i]->getObjectX()))));

		}
	
	object[5]->printData();
	for (int i = 2; i < FLAPPYBIRDOBJECTS; i++) {
		object[1]->enemyCollision = object[1]->collideWith(*object[i], object[1]->posVector);
		if (object[1]->enemyCollision) {
			std::cout << object[i]->getObjectX();
			object[1]->setStatus(ObjectStatus::Dead);
		}

	}
	if (object[1]->getStatus() == ObjectStatus::Dead) {
		game->sound->playDeathSound();
		game->sound->pauseMainMenuMusic();
		game->state = GameStates::LEVELPLAYERWIN;
	}


	if (object[1]->getVelocityY() < -50)
		std::cout << std::endl << object[1]->getVelocityY();
}

void FlappyBird::deleteAll()
{
	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		dltPtr(object[i]);
	}
}

void FlappyBird::handleEvents(GameStateManager * game)
{
	switch (game->state) {
	case GameStates::LEVELPLAYERWIN:
		game->changeState(LevelPlayerWins::getInstance(),hwnd);
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
