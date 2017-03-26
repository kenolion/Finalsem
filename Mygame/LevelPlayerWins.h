#ifndef LEVELPLAYERWINS_H		//ZER ADD
#define LEVELPLAYERWINS_H
#include "Game.h"
class LevelPlayerWins: public Game
{
public:

	GameObject * returnToMainMenuButton;
	GameObject * backgroundImage;
	GameObject * youWinTextLogo;
	GameObject * quitButton;


	Button *childrenPointer1;
	Button *childrenPointer2;

	bool initializeGame(HWND hwnd, GameEngine * game);
	void update(int gameTime, GameEngine * game);
	void collisions(GameEngine * game, int gameTime);
	void handleEvents(GameEngine *game);
	static LevelPlayerWins* getInstance() {
		return &winState;
	}


	void draw(GameEngine * game);
	void deleteAll();
protected:
	LevelPlayerWins() {}
	~LevelPlayerWins();
private:
	static LevelPlayerWins winState;


};

#endif