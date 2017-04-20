#include "Enemy.h"
#include "GameEngine.h"




Enemy::Enemy()
{

}


Enemy::~Enemy()
{
	for (int i = 0; i < 3; i++) {
		dltPtr(animation[i]);
	}
}

Enemy::Enemy(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass) :GameObject(x, y, scaling, animSpeed, mass)
{
	detectionRadius = 500.0f;  // 10 pixels	
	type = ObjectType::Enemy;
	animation[0] = new AnimationManager();
	animation[0]->initialize(96, 0, 96, 32, 3, true, 0, 0,5);				//idle				
	animation[1] = new AnimationManager();
	animation[1]->initialize(0, 0, 96, 32, 3, true, 0, 0,5);				//fly right
	animation[2] = new AnimationManager();
	animation[2]->initialize(0, 32, 96, 32, 3, true, 0, 0,5);				//fly left
	walkSpeed = 2.0f;
	prevCol = 1;
	prevRow = 1;
	face = 1;
	state = 0;
}

void Enemy::update(int &gameTime, GameEngine * game)
{
	for (int i = 0; i < gameTime; i++) {
		spriteWidth = animation[state]->getWidth();
		spriteHeight = animation[state]->getHeight();
		additionalXOffset = animation[state]->getAdditionalXOffset();
		additionalYOffset = animation[state]->getAdditionalYOffset();
		posVector += velocity;

		position = posVector;
		//setting the collision box
		collisionRect.left = posVector.x + col_xOffset  - positionOffset.x;
		collisionRect.right = posVector.x + spriteWidth  - col_xOffset - positionOffset.x;
		collisionRect.top = posVector.y + col_yOffset - positionOffset.y;
		collisionRect.bottom = posVector.y + spriteHeight*scaling.y - positionOffset.y;


		positionOffset.x = game->camera->getXOffset();
		positionOffset.y = game->camera->getYOffset();
		screenPos = position - positionOffset;
		animation[state]->start();
		if (animTimer >= REQFPS) {
			animTimer = 0;
			animation[state]->nextFrame();
		}
		animTimer += animation[state]->getAnimationSpeed();
	}
}

void Enemy::draw(GameEngine * game)
{
	CollisionBox[0] = { (float)collisionRect.left ,(float)collisionRect.top };
	CollisionBox[1] = { (float)collisionRect.left ,(float)collisionRect.bottom };
	CollisionBox[2] = { (float)collisionRect.right ,(float)collisionRect.bottom };
	CollisionBox[3] = { (float)collisionRect.right ,(float)collisionRect.top };
	CollisionBox[4] = { (float)collisionRect.left ,(float)collisionRect.top };
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
		if (path.back().row < getRow()) {
			velocity.y = -walkSpeed;
		}
		else if (path.back().row > getRow()){
			velocity.y = walkSpeed;
		}
		else if (path.back().col == getCollumn() && path.back().row == getRow())
		{
			state = 0;
			velocity.x = 0;
			velocity.y = 0;
			path.pop_back();
		}

	}
	else {
		prevCol = -1;
		prevRow = -1;
	}
}

void Enemy::moveXdirection()
{
	if (path.size() > 0) {
		if (path.back().col < getCollumn()){
			velocity.x = -walkSpeed;
			state = 2;
			face = -1;
		}
		else if (path.back().col > getCollumn()){
			velocity.x = walkSpeed;
			state = 1;
			face = 1;
		}
		else if (path.back().col == getCollumn() && path.back().row == getRow())
		{
			state = 0;
			velocity.x = 0;
			velocity.y = 0;
			path.pop_back();
		}

	}
	else {
		prevCol = -1;
		prevRow = -1;
	}


}




