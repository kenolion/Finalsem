#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "GameSprite.h"
#include <iostream>
#include "Constants.h"
#include "PlayerInput.h"
#include "AnimationManager.h"
#include "Node.h"
#include <vector>

class GameEngine;
class GameObject
{
public:

	GameObject();
	GameObject(float x, float y, D3DXVECTOR2 scaling, int animSpeed,int mass);
	GameObject(float x, float y, D3DXVECTOR2 scaling, int mass);
	int row;
	int column;
	int prevRow;
	int prevCol;
	~GameObject();
	virtual bool initialize(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, bool frameHorizontal, D3DXCOLOR color, float falseColl);
	virtual void update(int &gameTime, GameEngine * game) = 0;
	virtual void draw(GameEngine * game);
	virtual void physics(PlayerInput *input, int gameTime);

	//Sprite
	GameSprite *spriteClass;
	void setState(int state);
	void setFrame(int frame);
	float rotation;
	float getWidth();
	float getHeight();
	virtual bool getIsClicked();
	virtual void setIsClicked(bool click);
	

	//physics
	int counter;
	void setAcceleration(D3DXVECTOR2 accel);
	void setVelocity(float x, float y);
	virtual float getWalkSpeed();
	virtual float getJumpSpeed();
	float getDistance(GameObject * object);
	int getDetectionRadius();
	int detectionRadius;
	bool objectInRadius;
	D3DXVECTOR2 getAcceleration();
	D3DXVECTOR2 getVelocity();
	void setScaling(D3DXVECTOR2 scaling);
	void calculateVelocity();
	float getMass();
	bool collideWith(GameObject *object);
	bool getOnGround();
	void setOnGround(bool onGround);
	bool getAtCeiling();
	void setAtCeiling(bool onGround);
	void handleXAxisCollision();
	void handleYAxisCollision();
	virtual void moveXdirection();
	virtual void moveYdirection();
	D3DXVECTOR2 overlap;
	//TEMP data used for calculating physics
	D3DXVECTOR2 getObjectPos();
	void setPosition(float x, float y);
	D3DXVECTOR2 distance;				//used for storing distance between objects in the collision function of gameobject
	D3DXVECTOR2 posVector;				//temp vector
	D3DXVECTOR2 forceVector;
	ObjectStatus getStatus();
	void setStatus(ObjectStatus status);
	ObjectType getType();
	bool jump;
	//
	void printData(); // used to print players data
	void setMatrix(D3DXVECTOR2 scaling, D3DXVECTOR2 spriteCentre, float rotation, D3DXVECTOR2 position, GameEngine * game);	//scaling,spritecentre,rotation,position
	D3DXVECTOR2 CollisionBox[5]; //use for displaying lines

	//TILES
	TileType tile;
	virtual int getTileID();
	
	RECT spriteRect; // to cut out the prites
	RECT collisionRect; //used if you want to make additional rectangles to check for collision
	RECT legRect;
	int additionalXOffset; // use for offsetting the collision rectangle for certain animations
	int additionalYOffset;
	////////
	RECT headRect;
	RECT leftBodyRect;
	RECT rightBodyRect;




	bool legRectCollided;
	bool bodyRectCollided;

	bool pushedRightWall;
	bool pushesRightWall;

	bool pushedLeftWall;
	bool pushesLeftWall;

	bool wasOnGround;
	bool onGround;
	
	bool collided;

	bool wasAtCeiling;
	bool atCeiling;

	bool btmLeft;
	bool btmRight;
	bool topLeft;
	bool topRight;
	bool middleLeft;
	bool middleRight;


	D3DXVECTOR2 positionOffset;
	D3DXVECTOR2 screenPos;

	bool upArrowKey;
	bool downArrowKey;
	bool rightArrowKey;
	bool leftArrowKey;
	bool jumpKey;
	int face;
	int getRow();
	int getCollumn();
	std::vector<Node> path;
protected:
	//informational data(name, desc wtv u want)
	std::string name;
	std::string description;
	//physics data

	D3DXVECTOR2 oldPosition;
	D3DXVECTOR2 position;
	
	D3DXVECTOR2 oldVelocity;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 oldAcceleration;
	D3DXVECTOR2 scaling;
	float mass;
	ObjectStatus status;
	ObjectType type;
	D3DXVECTOR2 spriteCentre;
	D3DXMATRIX mat;
	//Bools

	

	//RECT COLLISION
	float col_width;
	float col_height;
	float col_xOffset;
	float col_yOffset;
	

	//SPRITE INFO
	D3DXVECTOR2 radius;			//if theres any
	D3DCOLOR color;
	
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