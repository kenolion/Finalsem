#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
class Enemy: public GameObject
{
public:
	Enemy();
	Enemy(float x, float y, D3DXVECTOR2 scaling, int animSpeed, float speed, int mass);
	~Enemy();
	void update(int &gameTime);
	


};

#endif