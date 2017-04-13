#include "Platform.h"
#include "GameEngine.h"




void Platform::update(int &gameTime, GameEngine * game)
{
	for (int i = 0; i < gameTime; i++) {
		positionOffset.x = game->camera->getXOffset();
		positionOffset.y = game->camera->getYOffset();
		screenPos = position - positionOffset;
		collisionRect.left = screenPos.x + col_xOffset;
		collisionRect.right = screenPos.x + spriteWidth - col_xOffset;
		collisionRect.top = screenPos.y + col_yOffset;
		collisionRect.bottom = screenPos.y + spriteHeight*scaling.y;
	}

}



Platform::Platform(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int tileWidth, int tileHeight, int tileType,int tileID) :GameObject(x, y, scaling, animSpeed)
{
	this->tileType = tileType;
	this->type = ObjectType::Platform;
	row = x;
	column = y;
	position.x = row*tileWidth;
	position.y = column*tileHeight;
}

bool Platform::initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color, float falseColl)
{
	GameObject::initialize(device3d, file, width, height, row, col, frameHorizontal, color, falseColl);
	this->tile = TileType::Block;
	if (tileType > 6) {
		state += tileType / 6.0f;
		frame = tileType % 6;
	}
	else {
		setFrame(tileType);
	}
	setState(state);
	return true;
}


Platform::~Platform()
{
}


int Platform::getTileID()
{
	return tileID;
}
