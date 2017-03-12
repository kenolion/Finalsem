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

	bool initializeGame(HWND hwnd, GameStateManager * game);
	void update(int gameTime, GameStateManager * game);
	void collisions(GameStateManager * game);
	void handleEvents(GameStateManager *game);
	static LevelPlayerWins* getInstance() {
		return &winState;
	}


	void draw(GameStateManager * game);
	void deleteAll();
protected:
	LevelPlayerWins() {}
	~LevelPlayerWins();
private:
	static LevelPlayerWins winState;


};

#endif