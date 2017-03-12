#ifndef CURSOR_H
#define CURSOR_H
#include "GameObject.h"

class Cursor : public GameObject
{
public:
	Cursor(float x, float y, D3DXVECTOR2 scaling, int animSpeed);
	~Cursor();
	void update(int &gameTime);

	
};

#endif