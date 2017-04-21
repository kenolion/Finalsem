#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "Game.h"
#include <time.h>
#include <math.h>

class LevelTwo :public Game
{
public:
	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void draw(GameEngine * game);
	void collisions(GameEngine * game, int gameTime);
	void deleteAll();
	void handleEvents(GameEngine *game);

	void multiplayer(GameEngine * game);

	GameObject *menuButton;

	GameObject * parallaxBG1;
	GameObject * parallaxBG2;

	GameObject * dungeonKey;
	GameObject * dungeonDoor;
	GameObject *tempObject;
	int timer;				//increase by 1 each time count reaches the targeted fps
	int counter;			// used to count 1 second

	bool keyObtained = false;

	static LevelTwo* getInstance() {
		return &level2State;
	}
private:
	static LevelTwo level2State;

	LevelTwo();
	~LevelTwo();
};

#endif
