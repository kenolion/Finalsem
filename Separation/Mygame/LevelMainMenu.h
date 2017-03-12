#ifndef LEVELMAINMENU_H			
#define LEVELMAINMENU_H

#include "Game.h"

class LevelMainMenu : public Game
{
public:

	GameObject * startButton;
	GameObject * quitButton;
	GameObject * backgroundImage;
	GameObject * gameLogo;

	Button *childrenPointer;
	Button *childrenPointer2;

	//YOU DONT NEED A HITBOXLINE POINTER OBJECT, BECAUSE GRAPHICS IS ALREADY DECLARED	Graphics * hitBoxLines;

	bool initializeGame(HWND hwnd, GameStateManager * game);
	void update(int gameTime, GameStateManager * game);
	void collisions(GameStateManager * game);
	void handleEvents(GameStateManager *game);

	void draw(GameStateManager * game);
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