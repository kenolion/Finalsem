#ifndef PICTURES_H
#define PICTURES_H
#include "GameObject.h"
class Pictures : public GameObject
{
public:
	Pictures();
	Pictures(float x, float y, D3DXVECTOR2 scaling);
	~Pictures();

	void update(int &gameTime);


};

#endif