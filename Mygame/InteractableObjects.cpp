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
		if (animTimer >= 60) {
			animTimer = 0;
			frame++;
			if (frame > maxFrame) {
				frame = maxFrame;
			}
		}
		animTimer += animSpeed;

	}
}