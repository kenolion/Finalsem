#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "Graphics.h"
#include "Button.h"


class UserInterface	
{
public:
	UserInterface();
	~UserInterface();

	void drawUIButton(LPD3DXLINE line, int x, int y, float startXA, float startYA, float startXB, float startYB, float startXC, float startYC, float startXD, float startYD);
	void initializeUIImages();

	Button * button;
	
};


#endif