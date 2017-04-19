#include "Player.h"


Player::Player(float x, float y, D3DXVECTOR2 scaling, int animSpeed,float speed,int mass) :GameObject(x, y, scaling, animSpeed,speed,mass)
{
	this->type = ObjectType::Player;
	onGround = false;
	jump = false;
}



void Player::update(int &gameTime)
{
	//std::cout << "X:" << position.x << "   " << std::endl;
	//std::cout << "Y:" << position.y << "   " << std::endl;
	//std::cout << "Velocity:" << velocity.x << "," << velocity.y << "   " << std::endl;
	
	if (status == ObjectStatus::Active) {

		for (int i = 0; i < gameTime; i++) {
			if (velocity.y > MAXYVELOCITY) {
				velocity.y = MAXYVELOCITY;
			}
			if (!enemyCollision) {
			position += velocity;
			}
			if(jump == true){
			jumpCD += 2.0;
			}
			
			if (animTimer >=REQFPS) {
				animTimer = 0;
				frame++;
				if (frame > maxFrame) {
					frame = 1;
				}
			}
			animTimer += animSpeed;

		}
	}
	else if(status == ObjectStatus::Dead){
		state = 4;

	}
}


bool Player::getOnGroundStatus()
{
	return onGround;
}

void Player::setGroundStatus(bool status)
{
	onGround = status;
}

Player::~Player()
{
}
