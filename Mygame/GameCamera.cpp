#include "GameCamera.h"



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
	xOffset = object->getObjectX() - GAME_WIDTH/2 + object->getWidth();
	yOffset = object->getObjectY() - GAME_HEIGHT/2 + object->getHeight();
}

GameCamera::~GameCamera()
{
}
