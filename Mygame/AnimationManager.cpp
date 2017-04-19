#include "AnimationManager.h"



void AnimationManager::initialize(int left, int top, int right, int bottom, int totalFrame, bool loop)
{
	topOffset = top;
	btmOffset = bottom;
	leftOffset = left;
	rightOffset = right;
	maxFrame = totalFrame;
	currentRow = 1;
	this->width = right / totalFrame;
	this->height = bottom;
	frame = 1;
	loopable = loop;
}

void AnimationManager::start()
{
	if (loopable && isEOS()) {
		frame = 1;
	}

}

void AnimationManager::nextFrame()
{
	if(frame!= maxFrame)
	frame++;
	if (frame > maxFrame) {
		if (loopable && isEOS())
			frame = 1;
	}


}

bool AnimationManager::isEOS()
{
	if (frame == maxFrame) {

		return true;
	}
	return false;
}

RECT AnimationManager::getFrame()
{
	spriteRect.top = topOffset;
	spriteRect.bottom = spriteRect.top + height;
	spriteRect.left = leftOffset + (frame - 1)*width;
	spriteRect.right = spriteRect.left + width;
	std::cout << frame << "  " << std::endl;
	return spriteRect;
}

AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}