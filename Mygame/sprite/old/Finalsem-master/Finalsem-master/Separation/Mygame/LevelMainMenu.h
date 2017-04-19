#ifndef LEVELMAINMENU_H			
#define LEVELMAINMENU_H

#include "Game.h"

class LevelMainMenu : public Game
{
public:

	GameObject * startButton;
	GameObject * quitButton;

	GameObject * backgroundImage;
	GameObject * backgroundImage2;
	GameObject * backgroundImage3;
	GameObject * backgroundImage4;

	GameObject * gameLogo;
	
	Button *childrenPointer;
	Button *childrenPointer2;

	//YOU DONT NEED A HITBOXLINE POINTER OBJECT, BECAUSE GRAPHICS IS ALREADY DECLARED	Graphics * hitBoxLines;

	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void collisions(GameEngine * game);
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