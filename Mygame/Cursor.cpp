#include "Cursor.h"



Cursor::Cursor(float x, float y, D3DXVECTOR2 scaling, int animSpeed):GameObject( x,  y, scaling,animSpeed)
{
	position.x = x;
	position.y = y;
}


Cursor::~Cursor()
{
}

void Cursor:: update(int &gameTime, GameEngine * game)
{
	for (int i = 0; i < gameTime; i++) {
		if (animTimer >= 60) {
			animTimer = 0;
			frame++;
			if (frame > maxFrame) {
				frame = 1;
			}
		}
		animTimer += animSpeed;
	}

}

