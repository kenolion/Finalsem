#ifndef PLATFORM_H
#define PLATFORM_H
#include "GameObject.h"

class Platform:public GameObject
{
public:

	void update(int &gameTime, GameEngine * game);
	int tileType;
	Platform(float x, float y, D3DXVECTOR2 scaling,int animSpeed, int tileWidth, int tileHeight,int tileType, int tileID);
	bool initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color, float falseColl);
	int getTileID();
	int tileID;
private:
	~Platform();
};

#endif // PLATFORM_H