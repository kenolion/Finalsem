#ifndef BUTTON_H
#define BUTTON_H
#include "GameObject.h"

class Button : public GameObject
{
public:

	//D3DX VARIABLES
	HRESULT hr;
	LPD3DXFONT font;
	//VARIABLES
	RECT buttonRect;				//Hitbox for the Button
	LPCSTR string;					//Text for the Button
	int noOfCharacters;				//Number of Characters of the text on the button
	int r, g, b;					//RGB colour to mainpulate the colour of the button.

	ButtonType buttonType;

	//FUNCTIONS
	Button(float x, float y, D3DXVECTOR2 scaling, int animSpeed, LPCSTR string,int noOfCharacters,int r, int g, int b, LPD3DXFONT font,GameStates state, ButtonType buttonType);

	void draw(GameEngine * game);
	void update(int &gameTime, GameEngine * game);
	GameStates state;
	~Button();
	bool onHover(int mouseX, int mouseY);
	bool isClicked(bool leftClickDown);

	void numberedTextInput(GameEngine * game);

	bool textButtonIsClicked = false;


	

	
};

#endif
