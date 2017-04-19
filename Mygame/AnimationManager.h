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
	int additionalXOffset;
	int additionalYOffset;
	int height;
	int width;
	RECT spriteRect;

public:
	void initialize(int left, int top, int right, int bottom,int totalFrame,bool loop,int additionalXOffset,int additionalYOffset);
	bool loopable;
	void start();
	void nextFrame();
	bool isEOS();
	RECT getFrame();
	int getHeight();
	int getWidth();
	int getAdditionalXOffset();
	int getAdditionalYOffset();
	AnimationManager();
	~AnimationManager();
};
#endif // !ANIMATIONMANAGER_H
