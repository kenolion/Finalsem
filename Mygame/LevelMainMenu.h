#ifndef LEVELMAINMENU_H			
#define LEVELMAINMENU_H

#include "Game.h"

class LevelMainMenu : public Game
{
public:
	GameObject * startButton;
	GameObject * quitButton;

	GameObject * connectButton;
	GameObject * hostButton;
	GameObject * acceptConnectionButton;
	GameObject * startClientThreadButton;

	GameObject * textInputButton;
	GameObject * hostTextInputButton;

	GameObject * backgroundImage;
	GameObject * gameLogo;


	bool alreadytrue = FALSE;
	bool alreadytrue2 = FALSE;
	bool alreadytrue3 = FALSE;
	bool alreadytrue4 = FALSE;
	bool alreadytrue5 = FALSE;
	bool alreadytrue6 = FALSE;
	bool sendTehPacketsAndReceiveThyPackets = FALSE;

	bool drawAcceptButton = FALSE;


	

	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void collisions(GameEngine * game,int gameTime);
	void handleEvents(GameEngine *game);

	void draw(GameEngine * game);
	void deleteAll();
	static LevelMainMenu * getInstance() {
		return &mainMenuState;
	}
private:
	static LevelMainMenu mainMenuState;

protected:
	LevelMainMenu();
	~LevelMainMenu();


	
		
};

#endif