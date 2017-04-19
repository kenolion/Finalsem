#ifndef PLATFORM_H
#define PLATFORM_H
#include "GameObject.h"

class Platform:public GameObject
{
public:

	void draw(GameEngine * game);
	void update(int &gameTime);
	Platform(float x, float y, D3DXVECTOR2 scaling,int animSpeed);
private:
	~Platform();
};

#endif // PLATFORM_H