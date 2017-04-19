#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	float walkSpeed;				//player and enemy has this which means i should make a class called moveable objects inheriting gameObjects
public:

	//void seekTarget(AI findpath,GameObject *object);
	Enemy();
	Enemy(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass);
	~Enemy();
	void update(int &gameTime, GameEngine * game);
	void draw(GameEngine * game);
	void moveXdirection();			//since enemies have their own way of moving 
	void moveYdirection();
	AnimationManager *animation[2];
};

#endif