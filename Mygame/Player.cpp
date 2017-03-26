#include "Player.h"
#include "PlayerInput.h"

Player::Player(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass) :GameObject(x, y, scaling, animSpeed, mass)
{
	this->type = ObjectType::Player;
	jump = false;
	fsm = CharacterState::Idle;
	jumpSpeed = -10.0f;
	walkSpeed = 10.0f;


}



void Player::update(int &gameTime, float xOffSet, float yOffSet)
{
	if (status == ObjectStatus::Active) {

		for (int i = 0; i < gameTime; i++) {
			setDrawingPoint(0, 0);

			position += velocity;
			positionOffset.x = xOffSet;
			positionOffset.y = yOffSet;

			std::cout << screenPos.x << std::endl;
			std::cout << xOffSet << "      " << std::endl;
			std::cout << position.y << std::endl;
			//position = { round(position.x), round(position.y) };
			if (position.y > GAME_HEIGHT - spriteHeight * 2) {
				position.y = GAME_HEIGHT - spriteHeight * 2;
				onGround = true;
			}
			else {
				onGround = false;
			}
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

void Player::physics(PlayerInput * input)
{
	oldPosition = position;
	oldVelocity = forceVector;

	wasOnGround = onGround;
	pushedRightWall = pushesRightWall;
	pushedLeftWall = pushesLeftWall;
	wasAtCeiling = atCeiling;

	switch (fsm) {
	case CharacterState::Idle:

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
			fsm = CharacterState::Jumping;
			break;
		}
		break;
	case CharacterState::Jumping:
		velocity.y += GRAVITY;

		velocity.y = min(velocity.y, 10.0f);

		if (input->rightArrowKey == input->leftArrowKey) {
			velocity.x = 0.0f;
		}
		else if (input->rightArrowKey) {
			if (pushesRightWall)
				velocity.x = 0.0f;
			else
				velocity.x = walkSpeed;

		}
		else if (input->leftArrowKey) {
			if (pushesLeftWall)
				velocity.x = 0.0f;
			else
				velocity.x = -walkSpeed;

		}
		if (onGround) {
			if (input->leftArrowKey == input->rightArrowKey) {
				fsm = CharacterState::Idle;
				velocity.x = 0.0f;
			}
			else {
				fsm = CharacterState::Walking;
				velocity.x = 0.0f;
			}
		}
		break;
	case CharacterState::Walking:
		//set to walking animation
		if (input->rightArrowKey == input->leftArrowKey) {
			//set to idle animation
			fsm = CharacterState::Idle;
			velocity = { 0,0 };
			break;
		}
		if (input->rightArrowKey) {
			if (pushesRightWall)
				velocity.x = 0.0f;
			else
				velocity.x = walkSpeed;
		}
		else if (input->leftArrowKey) {

			if (pushesLeftWall)
				velocity.x = 0.0f;
			else
				velocity.x = -walkSpeed;

		}
		if (input->jumpKey) {
			velocity.y = jumpSpeed;
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
