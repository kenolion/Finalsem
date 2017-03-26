#include "Pictures.h"



Pictures::Pictures()
{
}


Pictures::Pictures(float x, float y, D3DXVECTOR2 scaling,int animSpeed) : GameObject(x, y, scaling, animSpeed)
{

}

Pictures::~Pictures()
{
}

void Pictures::update(int &gameTime, float xOffSet, float yOffSet)
{
	for (int i = 0; i < gameTime; i++) {
		for (int i = 0; i < gameTime; i++) {
			//position += velocity;
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
}