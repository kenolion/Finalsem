#include "InteractableObjects.h"
#include "GameEngine.h"


InteractableObjects::InteractableObjects(float x, float y, D3DXVECTOR2 scaling, int animSpeed) : GameObject(x, y, scaling, animSpeed)
{
	type = ObjectType::InteractableObject;

}

InteractableObjects::~InteractableObjects()
{
}

void InteractableObjects::update(int &gameTime, GameEngine * game)
{
	for (int i = 0; i < gameTime; i++) {
		CollisionBox[0] = { (float)collisionRect.left ,(float)collisionRect.top };			//<---- this for player 
		CollisionBox[1] = { (float)collisionRect.left ,(float)collisionRect.bottom };
		CollisionBox[2] = { (float)collisionRect.right ,(float)collisionRect.bottom };
		CollisionBox[3] = { (float)collisionRect.right ,(float)collisionRect.top };
		CollisionBox[4] = { (float)collisionRect.left ,(float)collisionRect.top };
		//position += velocity;
		positionOffset.x = game->camera->getXOffset();
		positionOffset.y = game->camera->getYOffset();
		collisionRect.left = screenPos.x + col_xOffset;
		collisionRect.right = screenPos.x + spriteWidth;
		collisionRect.top = screenPos.y + col_yOffset;
		collisionRect.bottom = screenPos.y + spriteHeight*scaling.y;
	
		screenPos = position - positionOffset;
	
		if (position.x <= -100) {
			position.x = GAME_WIDTH;
		}
		if (position.y >= GAME_HEIGHT + 100)
		{
			position.y = 432;
		}
		if (animTimer >= 60) {
			animTimer = 0;
		}
		animTimer += animSpeed;

		if (status == ObjectStatus::Dead)
		{
			collisionRect.left -= GAME_WIDTH;
			collisionRect.right -= GAME_WIDTH;
			collisionRect.top -= GAME_HEIGHT;
			collisionRect.bottom -= GAME_HEIGHT;
		}
	}
}