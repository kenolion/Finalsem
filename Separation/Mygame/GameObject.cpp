#include "GameObject.h"
#include "GameEngine.h"
GameObject::GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed)
{
	position.x = x;
	position.y = y;
	this->scaling = scaling;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	state = 1;			//Start it at frame 1
	frame = 1;
	this->animSpeed = animSpeed;
}

GameObject::GameObject(float x, float y, D3DXVECTOR2 scaling)		// for objects without animation
{
	position.x = x;
	position.y = y;
	this->scaling = scaling;
	state = 1;			//Start it at frame 1
	frame = 1;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}


GameObject::GameObject()
{
}

GameObject::GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed, float speed, int mass)					// for moving objects
{
	position.x = x;
	position.y = y;
	this->scaling = scaling;
	
	this->speed = speed;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->mass = mass;
	state = 1;			//Start it at frame 1
	frame = 1;
	this->animSpeed = animSpeed;
}


GameObject::~GameObject()
{
	dltPtr(spriteClass);
}

bool GameObject::initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color, float falseColl)
{
	status = ObjectStatus::Active;
	spriteClass = new GameSprite();
	// SPRITE IS EMPTY
	this->frameHorizontal = frameHorizontal;
	spriteClass->initializeTex(device3d, file, width, height, row, col, color);  //When a game object is created, a game sprite is created.
	this->width = width*scaling.x;			//actual bitmap width
	this->height = height*scaling.y;			//actual bitmap height
	this->spriteRow = row;			//
	this->spriteCol = col;
	spriteHeight = height / spriteRow;
	spriteWidth = width / spriteCol;
	col_width = this->width * falseColl; //if number lower means collision box smaller than player
	col_height = this->height *falseColl;
	col_xOffset = (this->width - col_width) / 2;
	col_yOffset = (this->height - col_height) / 2;
	if (scaling.x > 1) {
		position.x += (spriteWidth / 2) * scaling.x;


	}
	if (scaling.y > 1) {
		if (position.y > 0)
			position.y -= (spriteHeight / 2) * scaling.y;
		
	}

	//for rectangle collision
	left = position.x + col_xOffset;
	right = position.x + spriteWidth;
	top = position.y + col_yOffset;
	bottom = position.y + spriteHeight*scaling.y;

	if (frameHorizontal)
	{
		spriteRect.top = (state - 1)*spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;
		spriteRect.left = (frame - 1)*spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;
	}
	else
	{
		spriteRect.top = (frame - 1)*spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;
		spriteRect.left = (state - 1)*spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;

	}
	if (frameHorizontal) {
		maxFrame = spriteCol;					

	}
	else {
		maxFrame = spriteRow;
	}


	return true;
}



void GameObject::draw(GameEngine * game)		//Function that draw sprite
{
	//for RECT collision
	left = position.x + col_xOffset;
	right = position.x + spriteWidth;
	top = position.y + col_yOffset;
	bottom = position.y + spriteHeight*scaling.y;

	if (frameHorizontal)					//Changes if the sprite sheet frames are going horizontally or vertically
	{
		spriteRect.top = (state - 1)*spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;
		spriteRect.left = (frame - 1)*spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;
	}
	else
	{
		spriteRect.top = (frame - 1)*spriteHeight;
		spriteRect.bottom = spriteRect.top + spriteHeight;
		spriteRect.left = (state - 1)*spriteWidth;
		spriteRect.right = spriteRect.left + spriteWidth;

	}

	spriteCentre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &position);
	game->sprite->SetTransform(&mat);
	if (game->sprite)
	{
		spriteClass->draw(game->sprite, spriteRect, color);
	}


}



ObjectStatus GameObject::getStatus()
{
	return status;
}

void GameObject::setStatus(ObjectStatus status)
{
	this->status = status;
}

ObjectType GameObject::getType()
{
	return type;
}

void GameObject::printData()
{
	if (type == ObjectType::Enemy) {
		//std::cout << "Player" << std::endl;
		std::cout << "velocity.y:	" << velocity.y << std::endl;
		//std::cout << "enemy collision:	" << enemyCollision << std::endl;
		//std::cout << "ground collision:	" << getOnGroundStatus() << std::endl;

	}



}

void GameObject::setMatrix(D3DXVECTOR2 scaling, D3DXVECTOR2 spriteCentre, float rotation, D3DXVECTOR2 position, GameEngine * game)
{

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &position);
	game->sprite->SetTransform(&mat);
}


void GameObject::setSpeed(float speed)		//Function to adjust the speed/velocity of the object
{
	this->speed = speed;
}

D3DXVECTOR2 GameObject::getObjectPos()
{
	return position;
}

float GameObject::getObjectX()
{
	return position.x;
}

float GameObject::getObjectY()
{
	return position.y;
}

void GameObject::setX(float x)
{
	position.x = x;
}


void GameObject::setY(float y)
{
	position.y = y;
}


float GameObject::getSpeed()
{
	return speed;
}

void GameObject::setState(int state)
{
	this->state = state;
}

void GameObject::setFrame(int frame)
{
	this->frame = frame;
}

bool GameObject::collideWith(GameObject &object, D3DXVECTOR2 &collisionVector)
{


	if (object.getType() == ObjectType::Enemy) {		//this suppose to be enemy
		if (bottom < object.top)return false;
		if (top > object.bottom)return false;
		if (right < object.left)return false;
		if (left > object.right)return false;
	}




	//distance = object.getObjectPos() - position;			// Distance = object2 position - object1 position		
	//
	//if (D3DXVec2Length(&distance) < (spriteCentre.x + object.spriteCentre.x)) {
	//	return true;
	//}


	//if (distance.y *distance.y + distance.x*distance.x < (spriteCentre.x + object.spriteCentre.x)*(spriteCentre.y + object.spriteCentre.y)) {			//it is squared to make value x and y positive if the player is on the right side of object or above object		
	//																																			// spritecentre = object radius
	//	return true;
	//}

	return true;
	//means there is collision
}


D3DXVECTOR2 GameObject::getAcceleration()
{
	return acceleration;
}

bool GameObject::getOnGroundStatus()
{
	return false;		// this function needs to be implemented if the object has an onground bool 
}

void GameObject::setGroundStatus(bool status)
{
}


D3DXVECTOR2 GameObject::getVelocity()
{
	return velocity;
}

float GameObject::getVelocityX()
{
	return velocity.x;
}

float GameObject::getVelocityY()
{
	return velocity.y;
}

void GameObject::setScaling(D3DXVECTOR2 scaling)
{
	this->scaling = scaling;
}

float GameObject::getMass()
{
	return mass;
}

void GameObject::setAcceleration(D3DXVECTOR2 accel)
{
	acceleration = accel;
}

void GameObject::setVelocity(D3DXVECTOR2 vel)
{
	velocity = vel;
}
