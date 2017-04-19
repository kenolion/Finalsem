#include "LevelMainMenu.h"
#include "FlappyBird.h"
#include "LevelPlayerWins.h"
#include "GameEngine.h"
#include "Button.h"
#include "Pictures.h"
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
	gameLogo = new Pictures(100, 100, D3DXVECTOR2(1.0f, 1.0f), 1);
	if (!gameLogo->initialize(game->graphics->device3d, "sprite\\gameLogo.png", 1130, 97, 1, 1, true, D3DCOLOR_XRGB(0, 0, 0), 1.0f)) {
		MessageBox(NULL, "There was an issue creating the game logo image", NULL, NULL);			//Device3d,sprite file name, width , height , row,collumn
		return initialize = false;
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------

	startButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, "Start Game", 10, 255, 155, 0, game->graphics->font, GameStates::LEVEL1, ButtonType::NORMAL); //X to print, Y to print position and scaling.
	//startButton->setX(50);
	//startButton->setY(600);
	startButton->setPosition(50, 600);

	if (!startButton->initialize(game->graphics->device3d, "sprite\\buttonTemplateAnimation.png", 1116, 76, 1, 4, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
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

	//---------------------------------------------------------------------------------------------------------------------------------------------
	hostButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, NULL, 10, 255, 155, 0, game->graphics->font, GameStates::HOSTSERVER, ButtonType::NORMAL);
	hostButton->setPosition(350, 600);
	if (!hostButton->initialize(game->graphics->device3d, "sprite\\buttonHost.png", 279, 75, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the host button", NULL, NULL);
		return initialize = false; //If false program wont run
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------
	connectButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, NULL, 10, 255, 155, 0, game->graphics->font, GameStates::CONNECTSTATE, ButtonType::NORMAL);
	connectButton->setPosition(650, 600);
	if (!connectButton->initialize(game->graphics->device3d, "sprite\\buttonConnect.png", 279, 75, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the connect button", NULL, NULL);
		return initialize = false; //If false program wont run
	}

	//---------------------------------------------------------------------------------------------------------------------------------------------
	textInputButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, game->ipAddress.c_str(), 15, 255, 155, 0, game->graphics->font, GameStates::NULLSTATE, ButtonType::TEXTBUTTON);
	textInputButton->setPosition(650, 450);
	if (!textInputButton->initialize(game->graphics->device3d, "sprite\\textInputButton.png", 558, 75, 1, 2, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the text input button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	hostTextInputButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, game->hostIpAddress.c_str(), 15, 255, 155, 0, game->graphics->font, GameStates::NULLSTATE, ButtonType::TEXTBUTTON);
	hostTextInputButton->setPosition(350, 450);
	if (!hostTextInputButton->initialize(game->graphics->device3d, "sprite\\textInputButton.png", 558, 75, 1, 2, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the host text input button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	acceptConnectionButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, NULL, 15, 255, 155, 0, game->graphics->font, GameStates::ACCEPTCONNECTION, ButtonType::NORMAL);
	acceptConnectionButton->setPosition(GAME_WIDTH + 350, GAME_HEIGHT + 250);
	if (!acceptConnectionButton->initialize(game->graphics->device3d, "sprite\\acceptConnectionButton.png", 279, 75, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the accept button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	startClientThreadButton = new Button(0, 0, D3DXVECTOR2(1.0f, 1.0f), 30, NULL, 15, 255, 155, 0, game->graphics->font, GameStates::STARTCLIENTTHREAD, ButtonType::NORMAL);
	startClientThreadButton->setPosition(GAME_WIDTH + 350, GAME_HEIGHT + 250);
	if (!startClientThreadButton->initialize(game->graphics->device3d, "sprite\\start client thread.png", 279, 75, 1, 1, true, D3DCOLOR_XRGB(255, 255, 255), 1.0f)) //Width, Height of the pic when printed in game, SpriteWidth, SpriteHeight, 
	{
		MessageBox(NULL, "There was an issue creating the accept button", NULL, NULL);
		return initialize = false; //If false program wont run
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------

	game->exit = false;
	game->state = GameStates::MENU;

	return initialize = true;

}

void LevelMainMenu::update(int gameTime, GameEngine * game)
{

	game->cursor->update(gameTime, game); //Update cursor according to mouseX and mouseY
	startButton->update(gameTime, game);
	quitButton->update(gameTime, game);
	connectButton->update(gameTime, game);
	hostButton->update(gameTime, game);
	textInputButton->update(gameTime, game);
	hostTextInputButton->update(gameTime, game);
	acceptConnectionButton->update(gameTime, game);
//	startClientThreadButton->update(gameTime, game);


	if (game->input->upArrowKey) {
		game->network->sendbuf = "up";

	}
	if (game->input->leftArrowKey) {
		game->network->sendbuf = "left";
	}
	if (game->input->rightArrowKey) {
		game->network->sendbuf = "right";
	}
	if (game->input->jumpKey) {
		game->network->sendbuf = "jump";
	}


	//if (game->input->leftClickDown)
	//{
	//	if (alreadytrue == FALSE)
	//	{
	//		printf("|SERVER|\n");
	//		game->network->resolveAddressAndPort("192.168.0.102");
	//		game->network->createServerSocket();
	//		game->network->bindServerSocket();
	//		game->network->listenOnSocket();
	//		alreadytrue = TRUE;
	//	}
	//}
	//if (game->input->downArrowKey)
	//{
	//	if (alreadytrue2 == FALSE)
	//	{
	//		printf("|CLIENT|\n");
	//		game->network->createClientSocket("192.168.0.102");
	//		game->network->connectClientSocket();
	//		alreadytrue2 = TRUE;
	//	}
	//}
	//if (game->input->leftArrowKey)
	//{
	//	if (alreadytrue3 == FALSE)
	//	{
	//		printf("|SERVER|\n");
	//		game->network->acceptConnection();
	//		alreadytrue3 = TRUE;
	//	}
	//}
	//if (game->input->rightArrowKey)
	//{
	//	if (alreadytrue4 == FALSE)
	//	{
	//		printf("|CLIENT|\n");
	//		game->netThread = game->network->spawn2();
	//		game->netThread.detach();
	//		
	//		alreadytrue4 = TRUE;
	//	}
	//}
	//if (game->input->upArrowKey)
	//{
	//	if (alreadytrue5 == FALSE)
	//	{
	//		printf("|SERVER END|\n");
	//		game->netThread = game->network->spawn();
	//		game->netThread.detach();
	//		alreadytrue5 = TRUE;
	//	}
	//}

	//if (game->input->zeroKey)
	//{
	//	if (alreadytrue6 == FALSE)
	//	{
	//		game->network->disconnectAndShutdownSocket();
	//		alreadytrue6 = TRUE;
	//	}
	//}

	


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
		game->pushState(FlappyBird::getInstance(), hwnd);
		break;
	case GameStates::CONNECTSTATE:
		if (alreadytrue2 == FALSE)
		{
			hostButton->setPosition(GAME_WIDTH + 100, GAME_HEIGHT + 100);
			hostTextInputButton->setPosition(GAME_WIDTH + 100, GAME_HEIGHT + 100);

			printf("REQUESTING CONNECTION WITH SERVER : \n");
			game->network->createClientSocket(game->ipAddress.c_str());
			game->network->connectClientSocket();

			game->netThread = game->network->spawn2();
			game->netThread.detach();

			startClientThreadButton->setPosition(550, 330);
		
			alreadytrue2 = TRUE;
		}
		break;
	case GameStates::HOSTSERVER:
		if (alreadytrue3 == FALSE)
		{
			connectButton->setPosition(GAME_WIDTH + 100, GAME_HEIGHT + 100);
			textInputButton->setPosition(GAME_WIDTH + 100, GAME_HEIGHT + 100);

			printf("HOSTING SERVER : \n");
			game->network->resolveAddressAndPort(game->hostIpAddress.c_str());
			game->network->createServerSocket();
			game->network->bindServerSocket();
			game->network->listenOnSocket();

			acceptConnectionButton->setPosition(350, 330);
			alreadytrue3 = TRUE;
		}
		break;
	case GameStates::ACCEPTCONNECTION:
	{
		if (alreadytrue4 == FALSE)
		game->network->acceptConnection();
		game->netThread = game->network->spawn();
		game->netThread.detach();
		alreadytrue4 = TRUE;
	}
	break;

	case GameStates::STARTCLIENTTHREAD:
	{
		if(alreadytrue5 == FALSE)
		game->netThread = game->network->spawn2();
		game->netThread.detach();
		alreadytrue5 = TRUE;

	}
	break;

	}
}

void LevelMainMenu::draw(GameEngine * game)
{
	game->graphics->clear(D3DCOLOR_XRGB(0, 0, 0)); //255 204 255 = Pink
	game->graphics->begin();

	game->graphics->createLine();
	game->graphics->lineBegin();

	game->sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//======================================================= Draw your Objects in Here =======================================================

	backgroundImage->draw(game);
	gameLogo->draw(game);
	startButton->draw(game);
	quitButton->draw(game);
	connectButton->draw(game);
	hostButton->draw(game);
	textInputButton->draw(game);
	hostTextInputButton->draw(game);
	acceptConnectionButton->draw(game);
	//startClientThreadButton->draw(game);

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
	dltPtr(connectButton);
	dltPtr(hostButton);
	dltPtr(textInputButton);
	dltPtr(hostTextInputButton);
	dltPtr(acceptConnectionButton);
	dltPtr(startClientThreadButton);
	dltPtr(backgroundImage);
	dltPtr(gameLogo);


}


LevelMainMenu::LevelMainMenu()
{
}


LevelMainMenu::~LevelMainMenu()
{
	freeAStar();
}

