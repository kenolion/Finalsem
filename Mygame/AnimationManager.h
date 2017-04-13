#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include <Windows.h>
#include <iostream>

class AnimationManager
{
private:
	int frame;
	int maxFrame;
	int row;
	int col;
	int currentRow;
	int topOffset;
	int btmOffset;
	int leftOffset;
	int rightOffset;
	int height;
	int width;
	RECT spriteRect;

public:
	void initialize(int left, int top, int right, int bottom,int totalFrame,bool loop);
	bool loopable;
	void start();
	void nextFrame();
	bool isEOS();
	RECT getFrame();
	AnimationManager();
	~AnimationManager();
};
#endif // !ANIMATIONMANAGER_H
