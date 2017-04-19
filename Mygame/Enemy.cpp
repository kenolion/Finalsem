#include "Enemy.h"
#include "GameEngine.h"




Enemy::Enemy()
{

}


Enemy::~Enemy()
{
	for (int i = 0; i < 5; i++) {
		dltPtr(animation[i]);
	}
}

Enemy::Enemy(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass) :GameObject(x, y, scaling, animSpeed, mass)
{
	detectionRadius = 500.0f;  // 10 pixels	
	type = ObjectType::Enemy;
	animation[0] = new AnimationManager();
	animation[0]->initialize(0, 0, 192, 48, 4, true, 0, 0);				//idlek
	animation[1] = new AnimationManager();
	animation[1]->initialize(192, 0, 192, 48, 6, true, 0, 0);				//walking
	walkSpeed = 5.0f;
	state = 0;
}

void Enemy::update(int &gameTime, GameEngine * game)
{
	for (int i = 0; i < gameTime; i++) {

		position += velocity;
		positionOffset.x = game->camera->getXOffset();
		positionOffset.y = game->camera->getYOffset();
		screenPos = position - positionOffset;
		animation[state]->start();
		if (animTimer >= REQFPS) {
			animTimer = 0;
			animation[state]->nextFrame();
		}
		animTimer += animSpeed;
	}
}

void Enemy::draw(GameEngine * game)
{

	spriteCentre = D3DXVECTOR2((spriteWidth) / 2, (spriteHeight) / 2);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &screenPos);
	game->sprite->SetTransform(&mat);
	if (game->sprite)
	{
		spriteClass->draw(game->sprite, animation[state]->getFrame(), color);				// implement this
	}

}

void Enemy::moveYdirection()
{
	if (path.size() > 0) {
		if (path.back().row < getRow())
			velocity.y = -walkSpeed;
		else if (path.back().row > getRow())
			velocity.y = walkSpeed;
		else if (path.back().col == getCollumn() && path.back().row == getRow()) 
		{
			velocity.x = 0;
			velocity.y = 0;
			path.pop_back();
		}
	}
}

void Enemy::moveXdirection()
{
	if (path.size() > 0) {
		if (path.back().col < getCollumn())
			velocity.x = -walkSpeed;
		else if (path.back().col > getCollumn())
			velocity.x = walkSpeed;
		else if (path.back().col == getCollumn() && path.back().row == getRow()) 
		{
			velocity.x = 0;
			velocity.y = 0;
			path.pop_back();
		}
	}
}




