#ifndef INTERACTABLEOBJECTS_H
#define INTERACTABLEOBJECTS_H
#include "GameObject.h"
class InteractableObjects : public GameObject
{
public:
	InteractableObjects(float x, float y, D3DXVECTOR2 scaling, int animSpeed);
	~InteractableObjects();

	void update(int &gameTime, GameEngine * game);

};

#endif