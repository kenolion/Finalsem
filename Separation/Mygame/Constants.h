

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Windows.h>
const int GAME_WIDTH = 1280;
const int GAME_HEIGHT = 720;
const char CLASS_NAME[] = "Keith Class";
const char GAME_TITTLE[] = "MyFirstGame";

const int GROUND_LEVEL = GAME_HEIGHT - 150;		// sets the height of ground 150 pixels
const float GRAVITY = 0.5f;
const float FRICTION = 0.97f;
const float PLAYERMAXVEL = 1.0f;
const int REQFPS = 60;

//LEVEL1
const int GOBJECTNUML1 = 5;
enum class ObjectStatus { Active, Dying, Dead };
enum class ObjectType { Enemy, Player, Platform };

enum class GameStates			//Strongly Type enumartions may come in handy if this framework includes a level editor, other states that might have it's own main menu, exit enum and etcetera.
{
	EXITPROGRAM,		//Array 0
	MENU,				//Array 1
	LEVEL1,				//Array 2
	LEVELPLAYERWIN		//ArreSTay 3
};

const int FLAPPYBIRDOBJECTS = 16;
const float MAXYVELOCITY = 7;

template<typename T>
inline void dltPtr(T& ptr) {
	if (ptr){
		delete ptr;
		ptr = NULL;
	}



}

static void setDrawingPoint(int x, int y)
{
	COORD coord; //Does not need to be define because if we right click COORD and go to definition it is already defined in another library
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}



#endif // !CONSTANTS_H