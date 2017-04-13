#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"


class Player:public GameObject
{
private:

public:
	// spriteData contains the data required to draw the image by Graphics::drawSprite()
	//int     cols;           // number of cols (1 to n) in multi-frame sprite
	//int     startFrame;     // first frame of current animation
	//int     endFrame;       // end frame of current animation
	//int     currentFrame;   // current frame of animation
	//float   frameDelay;     // how long between frames of animation
	//float   animTimer;      // animation timer
	//bool    loop;           // true to loop frames
	//bool    visible;        // true when visible
	//bool    animComplete;   // true when loop is false and endFrame has finished displaying
	Player(float x, float y,D3DXVECTOR2 scaling,int animSpeed,float speed,int mass);
	void update(int &gameTime);

	//Mario properties
	bool onGround;

	bool getOnGroundStatus();
	void setGroundStatus(bool status);
	~Player();
};

#endif // !PLAYER_H