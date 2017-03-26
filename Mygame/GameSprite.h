#ifndef GAMESPRITE_H
#define GAMESPRITE_H
#include <d3dx9.h>
#include <string>

class GameSprite
{
private:
	//attributes
	LPDIRECT3DTEXTURE9 tex;

public:
	GameSprite();
	void initializeTex(LPDIRECT3DDEVICE9 device3d, std::string file, int width, int height, int row, int col, D3DXCOLOR color);

	virtual void draw( LPD3DXSPRITE sprite, RECT spriteRect, D3DCOLOR color);
	~GameSprite();
};


#endif // !GAMEPSRITE_H