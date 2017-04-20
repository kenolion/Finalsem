#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H
#include "Game.h"
#include <time.h>
#include <math.h>


class FlappyBird:public Game
{
public:
	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void draw(GameEngine * game);
	void collisions(GameEngine * game, int gameTime);
	void deleteAll();
	void handleEvents(GameEngine *game);
	GameObject *enemy[2];

	
	GameObject *menuButton;
	GameObject *tempObject;
	GameObject * parallaxBG1;
	GameObject * parallaxBG2;
	GameObject * parallaxBG3;

	GameObject * dungeonKey;
	GameObject * dungeonDoor;

	int timer;				//increase by 1 each time count reaches the targeted fps


	bool keyObtained = false;


	static FlappyBird* getInstance() {
		return &level1State;
	}
private:
	static FlappyBird level1State;
protected:
	FlappyBird();
	~FlappyBird();
};

#endif // !FLAPPYBIRD_H