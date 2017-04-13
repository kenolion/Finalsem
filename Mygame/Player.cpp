#include "Player.h"
#include "GameEngine.h"

Player::Player(float x, float y, D3DXVECTOR2 scaling, int animSpeed, int mass) :GameObject(x, y, scaling, animSpeed, mass)
{
	this->type = ObjectType::Player;
	jump = false;
	fsm = CharacterState::Idle;
	jumpSpeed = -15.0f;
	walkSpeed = 3.0f;
	//animation[0] = new AnimationManager();
	//animation[0]->initialize(0, 183, 276, 86, 4, true);				//idle
	//animation[1] = new AnimationManager();
	//animation[1]->initialize(0, 91, 330, 92, 6, true);				//walking
	//animation[2] = new AnimationManager();
	//animation[2]->initialize(0, 0, 332, 91, 4, false);		//jumping
	//animation[3] = new AnimationManager();
	//animation[3]->initialize(0, 64, 0, 48, 1, true);
	//animation[4] = new AnimationManager();
	//animation[4]->initialize(184, 172, 167, 138, 4, true);

	animation[0] = new AnimationManager();
	animation[0]->initialize(0, 48, 192, 48, 4, true);				//idlek
	animation[1] = new AnimationManager();
	animation[1]->initialize(192, 0, 192, 48, 6, true);				//walking
	animation[2] = new AnimationManager();
	animation[2]->initialize(0, 144, 192, 48, 4, false);		//jumping

	animation[3] = new AnimationManager();
	animation[3]->initialize(0, 0, 192, 48, 4, true);		// idle left
	animation[4] = new AnimationManager();
	animation[4]->initialize(0, 96, 192, 48, 4, false); // jump left
	animation[5] = new AnimationManager();
	animation[5]->initialize(0, 192, 192, 48, 6, true); //wlaking
	face = 1;
}




void Player::update(int &gameTime, GameEngine * game)
{
	if (status == ObjectStatus::Active) {

		//std::cout << position.y << "        " << std::endl;
	//std::cout << onGround << std::endl;
		for (int i = 0; i < gameTime; i++) {
			position = posVector;
			//scaling = { (float)face,1.0f };
			positionOffset.x = game->camera->getXOffset();
			positionOffset.y = game->camera->getYOffset();

			screenPos = position - positionOffset;

			//std::cout << positionOffset.x << "     " << std::endl;
			//position = { round(position.x), round(position.y) };
			if (animTimer >= REQFPS) {
				animTimer = 0;
				animation[state]->nextFrame();
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
	setDrawingPoint(0, 0);
	switch (fsm) {
	case CharacterState::Idle:
		std::cout << "idle" << std::endl;

		
			if (face == 1)
				state = 0;
			else
				state = 3;
			animation[state]->start();
		
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

		std::cout << "jumping" << std::endl;
		
		animation[state]->start();

		if (!onGround) {
			velocity.y += GRAVITY;
			velocity.y = min(velocity.y, 10.0f);
		}
		if (input->rightArrowKey == input->leftArrowKey) {
			if (face == 1)
				state = 2;
			else
				state = 4;
			acceleration.x = 0.0f;
			//velocity.x = 0.0f;
		}
		else if (input->rightArrowKey) {
			face = 1;
			state = 2;
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
			face = -1;
			state = 4;
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


		if (animation[state]->isEOS())
			animation[state]->start();

		//set to walking animation
		std::cout << "walking" << std::endl;
		if (input->rightArrowKey == input->leftArrowKey) {
			//set to idle animation
			fsm = CharacterState::Idle;
			acceleration.x = 0.0f;
			velocity.x = 0.0f;
			break;
		}
		if (input->rightArrowKey) {
			face = 1;
			state = 1;
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
			face = -1;
			state = 5;
			if (pushesLeftWall) {
				
				velocity.x = 0.0f;
				acceleration.x = 0.0f;
			}
			else {
				acceleration.x = -walkSpeed;
				velocity.x = max(velocity.x, -2.0f);
			}
		}
		if (input->jumpKey && onGround) {

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

void Player::draw(GameEngine * game)
{

	//if (frameHorizontal)					//Changes if the sprite sheet frames are going horizontally or vertically
	//{
	//	spriteRect.top = (state - 1)*spriteHeight;
	//	spriteRect.bottom = spriteRect.top + spriteHeight;
	//	spriteRect.left = (frame - 1)*spriteWidth;
	//	spriteRect.right = spriteRect.left + spriteWidth;
	//}
	//else
	//{
	//	spriteRect.top = (frame - 1)*spriteHeight;
	//	spriteRect.bottom = spriteRect.top + spriteHeight;
	//	spriteRect.left = (state - 1)*spriteWidth;
	//	spriteRect.right = spriteRect.left + spriteWidth;

	//}

	spriteCentre = D3DXVECTOR2((spriteWidth) / 2, (spriteHeight) / 2);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &screenPos);
	game->sprite->SetTransform(&mat);
	if (game->sprite)
	{
		spriteClass->draw(game->sprite, animation[state]->getFrame(), color);
	}



}

float Player::getWalkSpeed()
{
	return walkSpeed;
}

float Player::getJumpSpeed()
{
	return jumpSpeed;
}


CharacterState Player::getCharacterState()
{
	return fsm;
}

Player::~Player()
{
	for (int i = 0; i < 5; i++) {
		dltPtr(animation[i]);
	}
}
