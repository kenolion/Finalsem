#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include <Windows.h>
#include <iostream>

class AnimationManager
{
private:
	int frame;

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
	int animationSpeed;
public:
	void initialize(int left, int top, int right, int bottom, int totalFrame, bool loop, int additionalXOffset, int additionalYOffset, int animationSpd, bool isReverse);
	bool isReverse;
	bool loopable;
	int maxFrame;
	void nextFrame();
	void start();
	bool isEOS();
	RECT getFrame();
	void setFrame(int frame);
	int getHeight();
	int getWidth();
	int getAdditionalXOffset();
	int getAdditionalYOffset();
	int getAnimationSpeed();

	AnimationManager();
	~AnimationManager();
};
#endif // !ANIMATIONMANAGER_H
