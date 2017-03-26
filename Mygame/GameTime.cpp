#include "GameTime.h"


bool GameTime::initialize(int fps)
{

	QueryPerformanceFrequency(&timer_freq);
	QueryPerformanceCounter(&time_now);
	QueryPerformanceCounter(&time_previous);
	Requested_FPS = fps;
	intervalsPerFrame = ((float)timer_freq.QuadPart / Requested_FPS);
	return true;
}

int GameTime::update()
{
	int framesToUpdate = 0;
	float intervalSinceLastUpdate;
	QueryPerformanceCounter(&time_now);
	intervalSinceLastUpdate = (float)time_now.QuadPart - (float)time_previous.QuadPart;

	framesToUpdate = (int)(intervalSinceLastUpdate / intervalsPerFrame);
	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&time_previous);

	}
	return framesToUpdate;
}



GameTime::GameTime()
{
}


GameTime::~GameTime()
{
}
