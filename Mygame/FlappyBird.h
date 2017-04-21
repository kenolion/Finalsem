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

	/*BOOBY TRAPS=====================================*/
	GameObject * arrowShooterLeft;
	GameObject * arrowShooterLeft2;
	GameObject * arrowShooterTop;
	GameObject * arrowShooterTop2;
	GameObject * arrow[2];
	GameObject * topArrow[2];
	GameObject * spikes[7];
	/*================================================*/


	/*PLAYERINTERACTABLE==============================*/
	GameObject * dungeonKey;
	GameObject * dungeonDoor;
	GameObject * tallGuyDoor;
	GameObject * tallGuySeconDoor;
	GameObject * fatGuySwitch;
	/*================================================*/

	GameObject * explosionSprite;

	int timer;				//increase by 1 each time count reaches the targeted fps
	int counter;			// used to count 1 second

	bool keyObtained = false;
	bool doOnce = true;
	bool teleportAble = false;
	

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