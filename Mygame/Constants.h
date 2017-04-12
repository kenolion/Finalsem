

#ifndef CONSTANTS_H
#define CONSTANTS_H

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
enum class ObjectStatus { Active, Dying, Dead };
enum class ObjectType { Enemy, Player, Platform };
enum class TileType {Block};
const int FLAPPYBIRDOBJECTS = 2;
const float MAXYVELOCITY = 7;

const int TILEROW = 17;
const int TILECOLUMN = 43;
const int TILEWIDTH = 48;
const int TILEHEIGHT = 48;

enum class GameStates			//Strongly Type enumartions may come in handy if this framework includes a level editor, other states that might have it's own main menu, exit enum and etcetera.
{
	EXITPROGRAM,		//Array 0
	MENU,				//Array 1
	LEVEL1,				//Array 2
	LEVELPLAYERWIN		//Array 3
};



template<typename T>
inline void dltPtr(T& ptr) {
	if (ptr){
		delete ptr;
		ptr = NULL;
	}



}
//



#endif // !CONSTANTS_H