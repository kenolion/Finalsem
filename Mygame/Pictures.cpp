#include "Pictures.h"



Pictures::Pictures()
{
}


Pictures::Pictures(float x, float y, D3DXVECTOR2 scaling, int animSpeed) : GameObject(x, y, scaling, animSpeed)
{
	status == ObjectStatus::Active;
}

Pictures::~Pictures()
{
}

void Pictures::update(int &gameTime, GameEngine * game)
{
	if (status == ObjectStatus::Active) {
		for (int i = 0; i < gameTime; i++) {
			//position += velocity;

			if (animTimer >= 60) {
				animTimer = 0;			//if i do like this den all pictures like background might or might not get affefctedyn
				frame++;
				if (frame == maxFrame && state == spriteRow) {
					status = ObjectStatus::Dead;
				}
				if (frame > maxFrame) {
					frame = 1;
					state++;
					if (state > spriteRow) {
						state = 1;

					}
				
				}
			}
			animTimer += animSpeed;

		}
	}
}