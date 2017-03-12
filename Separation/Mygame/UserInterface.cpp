#include "UserInterface.h"



UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::drawUIButton(LPD3DXLINE line,int x, int y, float startXA, float startYA, float startXB, float startYB, float startXC, float startYC, float startXD, float startYD)
{
	setDrawingPoint(x,y);
	D3DXVECTOR2 basicButtonVertices[] = { D3DXVECTOR2(startXA, startYA), D3DXVECTOR2(startXB, startYB) , D3DXVECTOR2(startXC, startYC), D3DXVECTOR2(startXD, startYD) };
	line->Draw(basicButtonVertices, 4, D3DCOLOR_XRGB(255, 255, 255)); //Number of coordinates and colour of line.
}

void UserInterface::initializeUIImages()
{
//	button->initialize(graphics->device3d, "sprite\\practical9.png", );
}


/*
void drawMainMenu() {
button->draw(10,3)


}

public button{

draw
onclick()


}

*/