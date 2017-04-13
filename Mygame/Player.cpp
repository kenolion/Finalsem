#include "Player.h"
#include "GameEngine.h"

Player::Player(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass) :GameObject(x, y, scaling, animSpeed, mass)
{
	this->type = ObjectType::Player;
	jump = false;
	fsm = CharacterState::Idle;
	jumpSpeed = -15.0f;
	walkSpeed = 5.0f;


}



void Player::update(int &gameTime, GameEngine * game)
{
	if (status == ObjectStatus::Active) {

		for (int i = 0; i < gameTime; i++) {
			//setDrawingPoint(0, 0);


			velocity += acceleration;
			posVector += velocity;
			collisionRect.left = posVector.x + col_xOffset - positionOffset.x;
			collisionRect.right = posVector.x + spriteWidth - col_xOffset - positionOffset.x;
			collisionRect.top = posVector.y + col_yOffset - positionOffset.y;
			collisionRect.bottom = posVector.y + spriteHeight*scaling.y + 5 - positionOffset.y;


			/*legRect.top = posVector.y + (spriteHeight * 2) / 3 - positionOffset.y;
			legRect.bottom = posVector.y + spriteHeight - positionOffset.y;
			legRect.left = collisionRect.left;
			legRect.right = collisionRect.right;*/


			if (!onGround && velocity.y < 0 && bodyRectCollided == true) {
				velocity.y = 0;
				acceleration.y = 0;
			}


			if (onGround && velocity.y > 0) {
				//position.y = oldPosition.y;


				position.y = row * TILEHEIGHT;
				posVector.y = position.y;
			}
			else {
				position.y = posVector.y;
			}
			if (pushesRightWall || pushesLeftWall) {
				//position.x = oldPosition.x;
				posVector.x = position.x;
			}
			else {
				position.x = posVector.x;
			}
			//position = posVector;
			positionOffset.x = game->camera->getXOffset();
			positionOffset.y = game->camera->getYOffset();
			std::cout << game->camera->getYOffset() << "   " << std::endl;

			screenPos = position - positionOffset;

			//std::cout << positionOffset.x << "     " << std::endl;
			//position = { round(position.x), round(position.y) };


			if (animTimer >= REQFPS) {
				animTimer = 0;
				frame++;
				if (frame > maxFrame) {
					frame = 1;
				}
			}
			animTimer += animSpeed;

		}
	}
	else if (status == ObjectStatus::Dead) {
		state = 4;

	}
}

void Player::physics(PlayerInput * input, int gameTime)
{

	//std::cout << "old pos :" << oldPosition.x << "           new pos :" << position.x << "       "<< std::endl;
	oldPosition = position;
	oldVelocity = velocity;

	wasOnGround = onGround;
	pushedRightWall = pushesRightWall;
	pushedLeftWall = pushesLeftWall;
	wasAtCeiling = atCeiling;
	//setDrawingPoint(0, 0);
	switch (fsm) {
	case CharacterState::Idle:
		std::cout << "idling     ";
		state = 1;			//set to idle state
		if (!onGround) {
			fsm = CharacterState::Jumping;
			break;
		}
		if (input->rightArrowKey != input->leftArrowKey) {
			fsm = CharacterState::Walking;
			break;
		}
		else if (input->jumpKey) {
			velocity.y = jumpSpeed;
			onGround = false;
			fsm = CharacterState::Jumping;
			break;

		}


		break;
	case CharacterState::Jumping:
		if (!onGround) {
			std::cout << "Jumping     ";
			velocity.y += GRAVITY;

			velocity.y = min(velocity.y, 15.0f);
		}
		if (input->rightArrowKey == input->leftArrowKey) {
			acceleration.x = 0.0f;
			//velocity.x = 0.0f;
		}
		else if (input->rightArrowKey) {
			if (pushesRightWall) {
				velocity.x = 0.0f;
				acceleration.x = 0.0f;
			}
			else {

				acceleration.x = walkSpeed;
				velocity.x = min(velocity.x, 2.0f);
			}
		}
		else if (input->leftArrowKey) {
			if (pushesLeftWall) {
				velocity.x = 0.0f;
				acceleration.x = 0.0f;
			}
			else {
				acceleration.x = -walkSpeed;
				velocity.x = max(velocity.x, -2.0f);
			}
		}
		if (onGround) {
			if (input->leftArrowKey == input->rightArrowKey) {
				fsm = CharacterState::Idle;
				velocity.x = 0.0f;
				velocity.y = 0.0f;
			}
			else {
				fsm = CharacterState::Walking;
				velocity.x = 0.0f;
			}
		}
		break;
	case CharacterState::Walking:
		//set to walking animation
		std::cout << "Walking     ";
		if (input->rightArrowKey == input->leftArrowKey) {
			//set to idle animation
			fsm = CharacterState::Idle;
			acceleration.x = 0.0f;
			velocity.x = 0.0f;
			break;
		}
		if (input->rightArrowKey) {
			if (pushesRightWall) {
				acceleration.x = 0.0f;
				velocity.x = 0.0f;
			}
			else {
				acceleration.x = walkSpeed;
				velocity.x = min(velocity.x, 2.0f);
			}
		}
		else if (input->leftArrowKey) {

			if (pushesLeftWall) {
				velocity.x = 0.0f;
				acceleration.x = 0.0f;
			}
			else {
				acceleration.x = -walkSpeed;
				velocity.x = max(velocity.x, -2.0f);
			}
		}
		if (input->jumpKey) {
			velocity.y = jumpSpeed;
			onGround = false;
			fsm = CharacterState::Jumping;
			//set animation here to jumping
			break;
		}
		else if (!onGround) {
			fsm = CharacterState::Jumping;
			break;
		}
		break;
	case CharacterState::LedgeGrab:

		break;
	}




}


CharacterState Player::getCharacterState()
{
	return fsm;
}

Player::~Player()
{
}
