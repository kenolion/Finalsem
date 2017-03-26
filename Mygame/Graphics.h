
#ifndef GRAPHICS_H
#define GRAPHICS_H
#define WIN32_LEAN_AND_MEAN
#include<d3d9.h> 
#include <d3dx9.h>
#include <Windows.h>
#include "Constants.h"
#include "GameSprite.h"
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#include <string>

class Graphics
{
private:
	LP_3D direct3d;
	int width;
	int height;
public:
	LP_3DDEVICE device3d;
	LPD3DXLINE line = NULL; 
	LPD3DXFONT font;
	HWND hwnd;
	HRESULT result;
	D3DPRESENT_PARAMETERS d3dpp;
	RECT fontRect;
	bool initialize(HWND hwnd,int w,int h);
	void clear(D3DCOLOR color);
	void begin();
	
	//=======================================================USED TO DRAW LINES and font IN YOUR LEVEL================================================================
	void createLine();  //Needs to be called in your level's draw function if you want to start creating lines. This initializes the line device.
	void lineBegin(); //Needs to be called in your level's draw function if you want to start creating lines. This begins the line device.
	void drawLine(D3DXVECTOR2 VECTOR[], int noOfCoordinates, int r, int g, int b); //Call this in your level's draw to draw lines.
	void lineEnd(); //Needs to be called in your level's draw function if you want to start creating lines. This ends the line device.
	void drawfont(std::string text,int number,int noOfChar,float x,float y,LPD3DXSPRITE sprite,D3DXCOLOR color, int bottom);
	//=======================================================================================================================================================

	void end();
	void present();
	void cleanup();
	
	Graphics();
	~Graphics();
	
};


#endif // !DXGRAPHICS_H
