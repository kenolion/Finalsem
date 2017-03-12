#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H
#include "Game.h"
#include <time.h>
#include <math.h>

class FlappyBird:public Game
{
public:
	bool initializeGame(HWND hwnd, GameStateManager * game);
	void update(int gameTime, GameStateManager * game);
	void draw(GameStateManager * game);
	void collisions(GameStateManager * game);
	void deleteAll();
	void handleEvents(GameStateManager *game);
	int randomNumber;

	GameObject *object[FLAPPYBIRDOBJECTS];
	GameObject *menuButton;

	Button* childrenPointer;
	D3DXVECTOR2 gravity;

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