#include "GameObject.h"
#include "GameEngine.h"

GameObject::GameObject(float x, float y, D3DXVECTOR2 scaling, int mass, int animSpeed)		// for objects without animation
{
	position.x = x;
	position.y = y;
	this->scaling = scaling;
	state = 1;			//Start it at frame 1
	frame = 1;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->mass = mass;
	this->animSpeed = animSpeed;
}


GameObject::GameObject()
{
}

GameObject::GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed)					// for moving objects
{
	position.x = x;
	position.y = y;
	this->scaling = scaling;

	color = D3DCOLOR_ARGB(255, 255, 255, 255);
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
	//col_xOffset = spriteWidth / 3;
	//col_yOffset = spriteHeight / 3;
	if (scaling.x > 1) {
		position.x += (spriteWidth / 2) * scaling.x;


	}
	if (scaling.y > 1) {
		if (position.y > 0)
			position.y -= (spriteHeight / 2) * scaling.y;

	}

	//for rectangle collision
	collisionRect.left = position.x + col_xOffset;
	collisionRect.right = position.x + spriteWidth;
	collisionRect.top = position.y + col_yOffset;
	collisionRect.bottom = position.y + spriteHeight*scaling.y;

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
	if (type == ObjectType::Player) {
		screenPos.y = position.y - spriteHeight;
		screenPos.x = position.x - spriteWidth;
		//	headRect.left = position.x + 6;
		//	headRect.right = headRect.left + 18;
		//	headRect.top = position.y + 3;
		//	headRect.bottom = headRect.top + 16;


		//	legRect.left = position.x + 10 +col_xOffset;
		//	legRect.right = headRect.left + 12;
		//	legRect.top = position.y + 33 + col_yOffset;
		//	legRect.bottom = headRect.top + 12;


		//	leftBodyRect.left = position.x ;
		//	leftBodyRect.right = leftBodyRect.left + 10;
		//	leftBodyRect.top = headRect.bottom;
		//	leftBodyRect.bottom = leftBodyRect.top + 10;
		///*	leftBodyRect.left = position.x + 6;
		//	leftBodyRect.right = headRect.left + 18;
		//	leftBodyRect.top = position.y + 3;
		//	leftBodyRect.bottom = headRect.top + 16;






	}
	posVector = position;
	return true;
}



void GameObject::draw(GameEngine * game)		//Function that draw sprite
{
	//for RECT collision



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
	if ( type == ObjectType::Platform) {


		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &screenPos);
	}
	else {
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &position);		// This code is for objects that are not affected by camera
	}
	game->sprite->SetTransform(&mat);
	if (game->sprite)
	{
		spriteClass->draw(game->sprite, spriteRect, color);
	}


}

void GameObject::physics(PlayerInput * input, int gameTime)
{
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
		std::cout << "velocity.y:	" << velocity.y << std::endl;
	}



}

void GameObject::setMatrix(D3DXVECTOR2 scaling, D3DXVECTOR2 spriteCentre, float rotation, D3DXVECTOR2 position, GameEngine * game)
{

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &position);
	game->sprite->SetTransform(&mat);
}

int GameObject::getTileID()
{
	return 0;
}



void GameObject::calculateVelocity()
{
	acceleration = forceVector / mass;
	velocity += acceleration;
}



D3DXVECTOR2 GameObject::getObjectPos()
{
	return position;
}

void GameObject::setPosition(float x, float y)
{

	position = D3DXVECTOR2(x, y);
}


void GameObject::setState(int state)
{
	this->state = state;
}

void GameObject::setFrame(int frame)
{
	this->frame = frame;
}

float GameObject::getWidth()
{
	return spriteWidth;
}

float GameObject::getHeight()
{
	return spriteHeight;
}

bool GameObject::collideWith(GameObject *object)
{


	if (object->getType() == ObjectType::Enemy) {
		if (collisionRect.bottom < object->collisionRect.top)return false;
		if (collisionRect.top > object->collisionRect.bottom)return false;
		if (collisionRect.right < object->collisionRect.left)return false;
		if (collisionRect.left > object->collisionRect.right)return false;
	}

	if (object->getType() == ObjectType::Platform) {
		if (tile == TileType::Block) {
			onGround = false;
			legRectCollided = true;
			bodyRectCollided = true;			// lets just assume true for now and if all the test fails it will still remain true
			if (legRect.bottom < object->collisionRect.top) legRectCollided = false;			//if false means theres no collision
			if (legRect.top > object->collisionRect.bottom) legRectCollided = false;
			if (legRect.right < object->collisionRect.left)legRectCollided = false;
			if (legRect.left > object->collisionRect.right)legRectCollided = false;
			if (collisionRect.bottom < object->collisionRect.top)  bodyRectCollided = false;
			if (collisionRect.top > object->collisionRect.bottom) bodyRectCollided = false;
			if (collisionRect.right < object->collisionRect.left) bodyRectCollided = false;
			if (collisionRect.left > object->collisionRect.right) bodyRectCollided = false;

			if (legRectCollided == false && bodyRectCollided == false) {
				return false;
			}

		}

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
	if (legRectCollided == true && bodyRectCollided == true) {
		onGround = true;

	}

	if (onGround && velocity.y > 0) {
		velocity.y = 0;
		position.y = object->position.y - object->spriteHeight;

	}


	return true;
	//means there is collision

}
bool GameObject::getOnGround()
{
	return onGround;
}

void GameObject::setOnGround(bool onGround)
{
	this->onGround = onGround;
}

bool GameObject::getAtCeiling()
{
	return onGround;
}

void GameObject::setAtCeiling(bool onGround)
{
	this->atCeiling = onGround;
}


void GameObject::moveXdirection()
{
	velocity.x += acceleration.x;
	posVector.x += velocity.x;


	collisionRect.left = posVector.x + col_xOffset - positionOffset.x;
	collisionRect.right = posVector.x + spriteWidth - col_xOffset - positionOffset.x;
	collisionRect.top = posVector.y + col_yOffset - positionOffset.y;
	collisionRect.bottom = posVector.y + spriteHeight*scaling.y - positionOffset.y;


}

void GameObject::moveYdirection()
{
	velocity.y += acceleration.y;
	posVector.y += velocity.y;

	collisionRect.left = posVector.x + col_xOffset - positionOffset.x;
	collisionRect.right = posVector.x + spriteWidth - col_xOffset - positionOffset.x;
	collisionRect.top = posVector.y + col_yOffset - positionOffset.y;
	collisionRect.bottom = posVector.y + spriteHeight*scaling.y - positionOffset.y;


}

void GameObject::handleXAxisCollision()
{
	//if (pushesLeftWall) {
	//	overlap.x = (collisionRect.left + positionOffset.x) - ((int)((collisionRect.right) / 48) * 48);
	//	//posVector.x -= overlap.x;
	//}



} 

void GameObject::handleYAxisCollision()
{

	if (onGround) {
		if((int)positionOffset.y % 48 == 0)
			overlap.y = (collisionRect.bottom) - ((int)(((collisionRect.bottom) / 48) * 48));
		else {
			overlap.y = (collisionRect.bottom+positionOffset.y-48) - ((int)((collisionRect.bottom + positionOffset.y - 48) / 48) * 48);
		}
		//std::cout << ((int)((((collisionRect.bottom + positionOffset.y - spriteHeight) / 48)) * 48) ) << "        " << std::endl;
		posVector.y -= overlap.y;
	}

	if (atCeiling) {
		overlap.y = (collisionRect.top) - (int)((ceil((collisionRect.bottom) / 48) * 48));
		posVector.y -= overlap.y;
		velocity.y = 0;

	}

}


D3DXVECTOR2 GameObject::getAcceleration()
{
	return acceleration;
}


D3DXVECTOR2 GameObject::getVelocity()
{
	return velocity;
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

void GameObject::setVelocity(float x, float y)
{
	velocity = D3DXVECTOR2(x, y);
}

float GameObject::getWalkSpeed()
{
	return 0.0f;
}

float GameObject::getJumpSpeed()
{
	return 0.0f;
}
