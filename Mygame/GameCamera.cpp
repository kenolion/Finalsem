#include "GameCamera.h"
#include "GameObject.h"


float GameCamera::getXOffset()
{
	return xOffset;
}

float GameCamera::getYOffset()
{
	return yOffset;
}

void GameCamera::move(float xAmt, float yAmt)
{
	xOffset += xAmt;
	yOffset += yAmt;
}

GameCamera::GameCamera(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void GameCamera::setXOffset(float xOffset) {
	this->xOffset = xOffset;

}

void GameCamera::setYOffset(float yOffset) {
	this->yOffset = yOffset;

}

void GameCamera::centerOnObject(GameObject * object)
{
	xOffset = object->getObjectPos().x - GAME_WIDTH / 2 + object->getWidth();
	yOffset = object->getObjectPos().y - GAME_HEIGHT / 2 +object->getHeight();

	if (xOffset < 0) {
		xOffset = 0;
	}
	else if (xOffset > TILECOLUMN *TILEWIDTH - GAME_WIDTH) {
		xOffset = TILECOLUMN *TILEWIDTH - GAME_WIDTH;
	}
	if (yOffset < 0) {
		yOffset = 0;
	}
	else if (yOffset > TILEROW *TILEHEIGHT - GAME_HEIGHT) {
		yOffset = TILEROW *TILEHEIGHT - GAME_HEIGHT;
	}

}

GameCamera::~GameCamera()
{
}
