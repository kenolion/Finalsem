#include "Platform.h"
#include "GameEngine.h"




void Platform::update(int &gameTime, float xOffSet, float yOffSet)
{
	for (int i = 0; i < gameTime; i++) {
		positionOffset.x = xOffSet;
		positionOffset.y = yOffSet;


	}

}



Platform::Platform(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int tileWidth, int tileHeight, int tileType) :GameObject(x, y, scaling, animSpeed)
{
	this->tileType = tileType;
	this->type = ObjectType::Platform;
	
	position.x = x*tileWidth;
	position.y = y*tileHeight;
}

bool Platform::initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color, float falseColl)
{
	GameObject::initialize(device3d, file, width, height, row, col, frameHorizontal, color, falseColl);
	this->tile = TileType::Block;
	if (tileType > 6) {
		state += tileType / 6.0f;
		setFrame(tileType % 6);
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
