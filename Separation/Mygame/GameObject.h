#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameSprite.h"
#include <iostream>
#include "Constants.h"
class GameEngine;

class GameObject
{
public:

	GameObject();
	GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed, float speed, int mass);			//x, y, scaling, animation, speed,mass											//
	GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed);		//Zer add
	GameObject(float x, float y, D3DXVECTOR2 scaling);
	

	~GameObject();
	virtual bool initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color,float falseColl);
	virtual void update(int &gameTime) = 0;
	virtual void draw(GameEngine * game);
	
	//Sprite
	GameSprite *spriteClass;
	
	void setState(int state);
	void setFrame(int frame);
	float rotation;


	//physics
	void setAcceleration(D3DXVECTOR2 accel);
	void setVelocity(D3DXVECTOR2 vel);
	D3DXVECTOR2 getAcceleration();
	virtual bool getOnGroundStatus();
	virtual void setGroundStatus(bool status);
	D3DXVECTOR2 getVelocity();
	float getVelocityX();
	float getVelocityY();
	void setScaling(D3DXVECTOR2 scaling);


	float getMass();
	bool collideWith(GameObject &object, D3DXVECTOR2 &collisionVector);
	float getSpeed();
	void setSpeed(float speed);


	bool enemyCollision;
	bool platformCollision;

	//TEMP data used for calculating physics
	D3DXVECTOR2 getObjectPos();
	float getObjectX();
	float getObjectY();
	void setX(float x);
	void setY(float y);

	D3DXVECTOR2 distance;				//used for storing distance between objects in the collision function of gameobject
	D3DXVECTOR2 posVector;
	D3DXVECTOR2 forceVector;
	ObjectStatus getStatus();
	void setStatus(ObjectStatus status);
	ObjectType getType();
	bool jump;
	int jumpCD;
	//
	void printData(); // used to print players data
	void setMatrix(D3DXVECTOR2 scaling,D3DXVECTOR2 spriteCentre,float rotation,D3DXVECTOR2 position, GameEngine * game);	//scaling,spritecentre,rotation,position
protected:
	//informational data(name, desc wtv u want)
	std::string name;
	std::string description;
	//physics data
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 scaling;
	float mass;
	float speed;
	ObjectStatus status;
	ObjectType type;
	D3DXVECTOR2 spriteCentre;
	D3DXMATRIX mat;
	//RECT COLLISION
	int left;
	int right;
	int top;
	int bottom;
	float col_width;
	float col_height;
	float col_xOffset;
	float col_yOffset;
	RECT collisionRect; //used if you want to make additional rectangles to check for collision
	

	//SPRITE INFO
	D3DXVECTOR2 radius;			//if theres any
	D3DCOLOR color;
	RECT spriteRect;
	int height;
	int width;
	int spriteRow;				// this int changes according to its sprite sheet
	int spriteCol;				//this int changes according to its sprite sheet
	int state;					// this variable changes according to the game loop
	int frame;					// this variable changes according to the game loop
	int spriteHeight;
	int spriteWidth;
	int maxFrame;
	bool frameHorizontal;
	int animSpeed;
	int animTimer;
};

#endif // !GAMEOBJECT_H