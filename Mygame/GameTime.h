#ifndef GAMETIME_H
#define GAMETIME_H

#include <iostream>
#include "Constants.h"
#include <Windows.h>
class GameTime
{
public:
	//float elapsedGameTime;
	//float totalGameTime;
	bool initialize(int);
	int update();
	GameTime();
	~GameTime();
	
private:
//	LONGLONG start;
	//float frequencySeconds;
	int Requested_FPS;
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	
	float intervalsPerFrame;
	
};

#endif // !GAMETIME_H
