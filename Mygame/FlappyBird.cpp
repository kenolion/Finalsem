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
#include "LevelYouFail.h"
FlappyBird FlappyBird::level1State;

bool FlappyBird::initializeGame(HWND hwnd, GameEngine * game)
{
	doOnce = true;

	mapName = "TileMap.txt";
	game->sound->playLevel1Music();
	game->sound->channel->setVolume(0.25f);
	

	object[1] = new Player(200, 248, D3DXVECTOR2(1.0f, 1.0f), 10, 5, 2);
	object[0] = new Player(GAME_WIDTH / 2, GAME_HEIGHT / 2, D3DXVECTOR2(1.0f, 1.0f), 10, 5, 1);
	enemy[0] = new Enemy(26 * TILEWIDTH, 12 * TILEHEIGHT, { 1.0f,1.0f }, 10, 1);
	parallaxBG1 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 0);
	parallaxBG2 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 0);
	parallaxBG3 = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 0);
	explosionSprite = new Pictures(0, 0, D3DXVECTOR2(1.0f, 1.0f), 15);

	

	/*BOOBY TRAPS=====================================*/
	arrowShooterLeft = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	arrowShooterLeft2 = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	arrowShooterTop = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	arrowShooterTop2 = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);

	for (int i = 0; i < 7; i++)
	{
		spikes[i] = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
		if (!spikes[i]->initialize(game->graphics->device3d, "sprite\\spikes.png", 45, 47, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 0.4f)) {
			MessageBox(NULL, "There was an issue creating the spike", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}

	}

	if (!arrowShooterLeft->initialize(game->graphics->device3d, "sprite\\ARROW SHOOTER.png", 45, 47, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f))
	{
		MessageBox(NULL, "There was an issue creating the arrow shooter right", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!arrowShooterLeft2->initialize(game->graphics->device3d, "sprite\\ARROW SHOOTER.png", 45, 47, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f))
	{
		MessageBox(NULL, "There was an issue creating the arrow shooter right", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!arrowShooterTop->initialize(game->graphics->device3d, "sprite\\ARROWSHOOTERTOP.png", 47,45, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f))
	{
		MessageBox(NULL, "There was an issue creating the arrow shooter top", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	if (!arrowShooterTop2->initialize(game->graphics->device3d, "sprite\\ARROWSHOOTERTOP.png", 47, 45, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f))
	{
		MessageBox(NULL, "There was an issue creating the arrow shooter top", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	for (int i = 0; i < 2; i++)
	{
		arrow[i] = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
		if (!arrow[i]->initialize(game->graphics->device3d, "sprite\\arrow.png", 45, 47, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
			MessageBox(NULL, "There was an issue creating the arrow", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}

		topArrow[i] = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
		if (!topArrow[i]->initialize(game->graphics->device3d, "sprite\\ARROWTOP.png", 47, 45, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
			MessageBox(NULL, "There was an issue creating the arrow", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}
	}

	arrowShooterLeft->setPosition(30 * TILEWIDTH, 4 * TILEHEIGHT); 
	arrowShooterLeft2->setPosition(30 * TILEWIDTH, 2 * TILEHEIGHT);
	arrowShooterTop->setPosition(33 * TILEWIDTH, 8 * TILEHEIGHT);
	arrowShooterTop2->setPosition(37 * TILEWIDTH, 8 * TILEHEIGHT);

	spikes[0]->setPosition(7 * TILEWIDTH, 11 * TILEHEIGHT); 
	spikes[1]->setPosition(15 * TILEWIDTH, 5 * TILEHEIGHT); 
	spikes[2]->setPosition(7 * TILEWIDTH, 5 * TILEHEIGHT);
	spikes[3]->setPosition(18 * TILEWIDTH, 5 * TILEHEIGHT);
	spikes[4]->setPosition(27 * TILEWIDTH, 14 * TILEHEIGHT);
	spikes[5]->setPosition(56 * TILEWIDTH, 14 * TILEHEIGHT); 
	spikes[6]->setPosition(28 * TILEWIDTH, 14* TILEHEIGHT);


	arrow[0]->setPosition(24 * TILEWIDTH, 2 * TILEHEIGHT); 
	arrow[1]->setPosition(30 * TILEWIDTH, 4 * TILEHEIGHT);

	topArrow[0]->setPosition(33 * TILEWIDTH, 9 * TILEHEIGHT);
	topArrow[1]->setPosition(37 * TILEWIDTH, 9 * TILEHEIGHT);

	/*================================================*/


	/*PLAYERINTERACTABLE==============================*/
	dungeonKey = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	dungeonDoor = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	tallGuyDoor = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	tallGuySeconDoor = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);
	fatGuySwitch = new InteractableObjects(0, 0, D3DXVECTOR2(1.0f, 1.0f), 1);

	if (!dungeonKey->initialize(game->graphics->device3d, "sprite\\dungeonkey.png", 49, 49, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	dungeonKey->setPosition(13 * TILEWIDTH, 5 * TILEHEIGHT);

	if (!dungeonDoor->initialize(game->graphics->device3d, "sprite\\dungeondoor.png", 49, 49, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	dungeonDoor->setPosition(60 * TILEWIDTH, 14 * TILEHEIGHT);

	if (!tallGuyDoor->initialize(game->graphics->device3d, "sprite\\doorforTallGuy.png", 180, 94, 1, 2, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the tall guy door", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	tallGuyDoor->setFrame(1);
	tallGuyDoor->setPosition(33 * TILEWIDTH, 13 * TILEHEIGHT);

	if (!tallGuySeconDoor->initialize(game->graphics->device3d, "sprite\\doorforTallGuy.png", 180, 94, 1, 2, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the tall guy door", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	tallGuySeconDoor->setFrame(1);
	tallGuySeconDoor->setPosition(52 * TILEWIDTH, 13 * TILEHEIGHT);

	if (!fatGuySwitch->initialize(game->graphics->device3d, "sprite\\greenButton.png", 90, 47, 1, 2, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the green switch", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}
	fatGuySwitch->setPosition(47 * TILEWIDTH, 2 * TILEHEIGHT);

		/*================================================*/
		if (!explosionSprite->initialize(game->graphics->device3d, "sprite\\explosionSprite.png", 320, 320, 5, 5, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) {
			MessageBox(NULL, "There was an issue creating the boom sprite ????", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}

		if (!object[0]->initialize(game->graphics->device3d, "sprite\\tallguy.png", 1024, 512, 5, 10, true, D3DCOLOR_XRGB(0, 0, 0), 0.97f)) {			//512 256 5 10
			MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);				//Device3d,sprite file name, width , height , row,collumn
			return initialize = false;
		}

		if (!object[1]->initialize(game->graphics->device3d, "sprite\\fatguysmall.png", 512, 512, 6, 8, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
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
		explosionSprite->setStatus(ObjectStatus::Dying);
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

			if (enemy[0]->getDistance(object[i]) < enemy[0]->detectionRadius) {//calculate distance and current object
																			   //enemy[0]->objectInRadius = true; // player is in the radius
				if (counter >= 60) {
					findPath(enemy[0], object[i]->getObjectPos(), game->camera->getXOffset(), game->camera->getYOffset(), object[i]->getWidth(), object[i]->getHeight());

					counter = 0;
				}
				enemy[0]->moveXdirection();
				enemy[0]->moveYdirection();
			}

			if (dungeonKey->collideWith(object[i]))
			{
				game->sound->playPickUpKeySound();
				keyObtained = true;
				dungeonKey->setStatus(ObjectStatus::Dead);

			}

			if (dungeonDoor->collideWith(object[0]))
			{
				if (keyObtained == true);
				{
					object[0]->setStatus(ObjectStatus::Waiting);
				}
			}
		
			if (tallGuyDoor->collideWith(object[i]))
			{
				if (teleportAble == true)
				{
					object[0]->posVector = { 55 * TILEWIDTH, 14 * TILEHEIGHT };
				}
			}

			if (fatGuySwitch->collideWith(object[i]))
			{
				tallGuyDoor->setFrame(2);
				tallGuySeconDoor->setFrame(2);
				fatGuySwitch->setFrame(2);
				teleportAble = true;
				std::cout << "touch switch;\n";
			}

		/*	for (int i = 0; i < 7; i++)
			{

				if (spikes[i]->collideWith(object[0]))
				{
					object[0]->setStatus(ObjectStatus::Dead);
				}

			}

			for (int i = 0; i < 2; i++)
			{
				if (arrow[i]->collideWith(object[0]))
				{
					object[0]->setStatus(ObjectStatus::Dead);
				}

				if (topArrow[i]->collideWith(object[0]))
				{
					object[0]->setStatus(ObjectStatus::Dead);
				}
			}*/
				
		}
		game->network->counter++;
		counter++;
	}


	
}


void FlappyBird::update(int gameTime, GameEngine * game)
{
	//if (game->input->windowsLeftClickDown) {
	//	findPath(enemy[0], game->cursor->getObjectPos(), game->camera->getXOffset(), game->camera->getYOffset(),0,0);
	//}

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

	for (int i = 0; i < 7; i++)
	{
		spikes[i]->update(gameTime, game);
	}

	arrowShooterLeft->update(gameTime, game);
	arrowShooterLeft2->update(gameTime, game);
	arrowShooterTop->update(gameTime, game);
	arrowShooterTop2->update(gameTime, game);

	arrow[0]->setPosition(arrow[0]->getObjectPos().x - 5, arrow[0]->getObjectPos().y);
	arrow[1]->setPosition(arrow[1]->getObjectPos().x - 5, arrow[1]->getObjectPos().y);

	topArrow[0]->setPosition(topArrow[0]->getObjectPos().x, topArrow[0]->getObjectPos().y + 5);
	topArrow[1]->setPosition(topArrow[1]->getObjectPos().x, topArrow[1]->getObjectPos().y + 2);

	for (int i = 0; i < 2; i++)
	{
		arrow[i]->update(gameTime, game);
		topArrow[i]->update(gameTime, game);
	}

	tallGuyDoor->update(gameTime, game);
	tallGuySeconDoor->update(gameTime, game);

	fatGuySwitch->update(gameTime, game);

	explosionSprite->update(gameTime, game);

	game->cursor->update(gameTime, game);

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
//	game->graphics->drawfont("Key obtained, next level door unlocked", NULL, 38, 300, 300, game->sprite, D3DCOLOR_XRGB(10, 255, 255), 700);
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



	for (int i = 0; i < 7; i++)
	{
		spikes[i]->draw(game);
	}

	arrowShooterLeft->draw(game);
	arrowShooterLeft2->draw(game);
	arrowShooterTop->draw(game);
	arrowShooterTop2->draw(game);

	for (int i = 0; i < 2; i++)
	{
		arrow[i]->draw(game);
		topArrow[i]->draw(game);
	}


	for (int i = 0; i < FLAPPYBIRDOBJECTS; i++) {
		object[i]->draw(game);
	}

	tallGuyDoor->draw(game);
	tallGuySeconDoor->draw(game);
	fatGuySwitch->draw(game);
	if (object[0]->getStatus() == ObjectStatus::Dead)
	{

		if (doOnce == true)				
		{
			game->sound->playDeathSound();
			game->sound->playExplosionSound();
			explosionSprite->setStatus(ObjectStatus::Active);
			explosionSprite->setPosition(object[0]->screenPos.x, object[0]->screenPos.y);
			doOnce = false;
		}
		
	}if (object[1]->getStatus() == ObjectStatus::Dead)
	{

		if (doOnce == true)
		{
			game->sound->playDeathSound();
			game->sound->playExplosionSound();
			explosionSprite->setStatus(ObjectStatus::Active);
			explosionSprite->setPosition(object[1]->screenPos.x, object[1]->screenPos.y);
			doOnce = false;
		}

	}
	enemy[0]->draw(game);
	menuButton->draw(game);
	

	explosionSprite->draw(game);
	game->cursor->setMatrix(D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, D3DXVECTOR2(GAME_WIDTH / 2, 25), game);		//Set this to draw my font
	game->graphics->drawfont("Score : ", timer * 10, 13, 500, 50, game->sprite, D3DCOLOR_XRGB(255, 0, 0), 30);			// last parameter depends on the size of your font
	game->cursor->draw(game);
	game->sprite->End();
	game->graphics->lineBegin();
	game->graphics->drawLine(lines, enemy[0]->path.size(), 255, 0, 0);

	for (int i = 0; i < 7; i++)
	{
		game->graphics->drawLine(spikes[i]->CollisionBox, 5, 255, 0, 0);
	}

	for (int i = 0; i < 2; i++)
	{
		game->graphics->drawLine(arrow[i]->CollisionBox, 5, 255, 0, 0);
	//	game->graphics->drawLine(topArrow[i]->CollisionBox, 5, 255, 0, 0);
	}

	game->graphics->drawLine(tallGuyDoor->CollisionBox, 5, 255, 0, 0);
	game->graphics->drawLine(tallGuySeconDoor->CollisionBox, 5, 255, 0, 0);

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

	for (int i = 0; i <7; i++)
	{
		dltPtr(spikes[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		dltPtr(topArrow[i]);
		dltPtr(arrow[i]);
	}

	dltPtr(arrowShooterLeft);
	dltPtr(arrowShooterLeft2);

	dltPtr(arrowShooterTop);
	dltPtr(arrowShooterTop2);

	dltPtr(dungeonKey);
	dltPtr(dungeonDoor);
	dltPtr(fatGuySwitch);
	dltPtr(tallGuySeconDoor);
	dltPtr(tallGuyDoor);

	dltPtr(enemy[0]);

	//freeAStar();

}

void FlappyBird::handleEvents(GameEngine * game)
{
	if (explosionSprite->getStatus() == ObjectStatus::Dead) {			
		game->state = GameStates::LEVELYouFail;
	
	}
	switch (game->state) {
	case GameStates::LEVELPLAYERWIN:
		game->changeState(LevelPlayerWins::getInstance(), hwnd);
		break;
	case GameStates::MENU:
		game->sound->pauseLevel1Music();
		game->popState();
		break;
	case GameStates::LEVEL2:
		game->sound->pauseLevel1Music();
		game->changeState(LevelTwo::getInstance(), hwnd);
		break;
	case GameStates::LEVELYouFail:
		game->sound->pauseLevel1Music();	//does it work in multiplayer tho		
		game->changeState(LevelYouFail::getInstance(), hwnd);
		break;
	}

}


FlappyBird::FlappyBird()
{

}


FlappyBird::~FlappyBird()
{

}
