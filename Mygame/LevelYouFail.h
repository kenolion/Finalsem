#ifndef LEVELYouFail_H	
#define LEVELYouFail_H	
#include "Game.h"

class LevelYouFail : public Game
{
public:

	GameObject * returnToMainMenuButton;
	GameObject * quitButton;
	GameObject * gameOverText;
	GameObject * deadTallGuyPic;
	GameObject * deadFatGuyPic;

	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void collisions(GameEngine * game, int gameTime);
	void handleEvents(GameEngine *game);
	static LevelYouFail * getInstance() {
		return &levelfail;
	}


	void draw(GameEngine * game);
	void deleteAll();

protected:
	LevelYouFail();
	~LevelYouFail();
private:
	static LevelYouFail levelfail;


};

#endif