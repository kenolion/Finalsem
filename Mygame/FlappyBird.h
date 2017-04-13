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

	void multiplayer(GameEngine * game);
	
	GameObject *object[FLAPPYBIRDOBJECTS];
	GameObject *menuButton;

	GameObject * parallaxBG1;
	GameObject * parallaxBG2;
	GameObject * parallaxBG3;

	int timer;				//increase by 1 each time count reaches the targeted fps
	int counter;			// used to count 1 second

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