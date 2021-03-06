#include "AnimationManager.h"



void AnimationManager::initialize(int left, int top, int right, int bottom, int totalFrame, bool loop, int additionalXOffset, int additionalYOffset, int animationSpd, bool isReverse)
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
	animationSpeed = animationSpd;
	this->additionalXOffset = additionalXOffset;
	this->additionalYOffset = additionalYOffset;
	loopable = loop;
	this->isReverse = isReverse;

}

void AnimationManager::start()
{
	if (loopable && isEOS() && !isReverse) {
		frame = 1;
	}
	else if (loopable && isEOS() && isReverse) {
		frame = maxFrame;
	}

}

void AnimationManager::nextFrame()
{
	if (!isReverse) {
		if (frame != maxFrame)
			frame++;
		if (frame > maxFrame) {
			if (loopable && isEOS())
				frame = 1;
		}
	}
	else {
		if (frame != 1)
			frame--;
		if (frame < 1) {
			if (loopable && isEOS())
				frame = maxFrame;
		}
	}

}

bool AnimationManager::isEOS()
{
	if (!isReverse) {
		if (frame == maxFrame) {

			return true;
		}
		return false;
	}
	else {
		if (frame == 1) {

			return true;
		}
		return false;
	}
}

RECT AnimationManager::getFrame()
{
	spriteRect.top = topOffset;
	spriteRect.bottom = spriteRect.top + btmOffset;
	spriteRect.left = leftOffset + (frame - 1)*width;
	spriteRect.right = spriteRect.left + width;
	//std::cout << frame << "  " << std::endl;
	return spriteRect;
}

void AnimationManager::setFrame(int frame)
{
	this->frame = frame;
}

int AnimationManager::getHeight()
{
	return height;
}

int AnimationManager::getWidth()
{
	return width;
}

int AnimationManager::getAdditionalXOffset()
{
	return additionalXOffset;
}

int AnimationManager::getAdditionalYOffset()
{
	return additionalYOffset;
}

int AnimationManager::getAnimationSpeed()
{
	return animationSpeed;
}

AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}
