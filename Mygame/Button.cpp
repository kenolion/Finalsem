#include "Button.h"
#include "GameEngine.h"


Button::Button(float x, float y, D3DXVECTOR2 scaling, int animSpeed, LPCSTR string, int noOfCharacters, int r, int g, int b, LPD3DXFONT font, GameStates state, ButtonType buttonType) : GameObject(x, y, scaling, animSpeed)
{
	this->string = string;
	this->noOfCharacters = noOfCharacters;
	this->r = r;
	this->g = g;
	this->b = b;
	this->font = font;
	this->state = state;
	this->buttonType = buttonType;
	isClicked = false;
}

void Button::physics(PlayerInput * input, int gameTime)
{



}

Button::~Button()
{

}



bool Button::onHover(int mouseX, int mouseY)
{
	if (mouseX >= position.x && mouseX <= position.x + spriteWidth)
	{
		if (mouseY >= position.y&& mouseY <= position.y + spriteHeight)
		{
			return true;
		}
	}
	return false;
}

bool Button::getIsClicked()
{
	return isClicked;
}

void Button::setIsClicked(bool click)
{
	isClicked = click;
}



void Button::draw(GameEngine * game) {

	GameObject::draw(game);
	buttonRect.top = spriteHeight / 2 - 10;
	buttonRect.bottom = spriteRect.top + 200;
	buttonRect.left = spriteWidth / 2 - 60;
	buttonRect.right = spriteRect.left + 300;

	font->DrawText(game->sprite,														//(1st Parameter) [LPD3DX10SPRITE] Pointer to an ID3DX10Sprite object that contains the string you wish to draw. Can be NULL, in which case Direct3D will render the string with its own sprite object. To improve efficiency, a sprite object should be specified if ID3DX10Font::DrawText is to be called more than once in a row.
		string,																//(2nd Parameter) [LPCTSTR] Pointer to a string to draw. If UNICODE is defined, this parameter type resolves to an LPCWSTR, otherwise, the type resolves to an LPCSTR. If the Count parameter is -1, the string must be NULL terminated.	
		noOfCharacters, 														//(3rd Parameter) [INT] The number of characters in the string. If Count is -1, then the pString parameter is assumed to be a pointer to a sprite containing a NULL-terminated string and ID3DX10Font::DrawText computes the character count automatically.	
		&buttonRect,														    //(4th Parameter) [LPRECT] Pointer to a RECT structure that contains the rectangle, in logical coordinates, in which the text is to be formatted. As with any RECT object, the coordinate value of the rectangle's right side must be greater than that of its left side. Likewise, the coordinate value of the bottom must be greater than that of the top.	
		0, 																		//(5th Parameter) [UINT] Specify the method of formatting the text.It can be any combination of the following values : REFER FontFormats.txt													
		D3DCOLOR_XRGB(r, g, b)); //MOUSE X COORDINATE DRAWING POSITION		    //(6th Parameter) [D3DXCOLOR] Colour of the text	


	//font->DrawText(sprite,														//(1st Parameter) [LPD3DX10SPRITE] Pointer to an ID3DX10Sprite object that contains the string you wish to draw. Can be NULL, in which case Direct3D will render the string with its own sprite object. To improve efficiency, a sprite object should be specified if ID3DX10Font::DrawText is to be called more than once in a row.
	//	"burdenben",																//(2nd Parameter) [LPCTSTR] Pointer to a string to draw. If UNICODE is defined, this parameter type resolves to an LPCWSTR, otherwise, the type resolves to an LPCSTR. If the Count parameter is -1, the string must be NULL terminated.	
	//	15, 																	//(3rd Parameter) [INT] The number of characters in the string. If Count is -1, then the pString parameter is assumed to be a pointer to a sprite containing a NULL-terminated string and ID3DX10Font::DrawText computes the character count automatically.	
	//	&buttonRect,														    //(4th Parameter) [LPRECT] Pointer to a RECT structure that contains the rectangle, in logical coordinates, in which the text is to be formatted. As with any RECT object, the coordinate value of the rectangle's right side must be greater than that of its left side. Likewise, the coordinate value of the bottom must be greater than that of the top.	
	//	0, 																		//(5th Parameter) [UINT] Specify the method of formatting the text.It can be any combination of the following values : REFER FontFormats.txt													
	//	D3DCOLOR_XRGB(255, 255, 255)); //MOUSE X COORDINATE DRAWING POSITION		    //(6th Parameter) [D3DXCOLOR] Colour of the text	
}

void Button::update(int &gameTime, GameEngine * game)
{

	for (int i = 0; i < gameTime; i++) {
		if (onHover(game->input->mouseX, game->input->mouseY))
		{
			if (game->input->leftClickDown)
			{
				if (!isClicked) {
					if (counter >= 30) {
						isClicked = true;
						std::cout << "clickeD!" << std::endl;
						counter = 0;
					}
				}

				else {
					if(counter >=30){
					isClicked = false;
					std::cout << "not click" << std::endl;
					counter = 0;
					}
				}
				game->state = state;
			}


			frame = maxFrame;
		}
		else {
			if (buttonType == ButtonType::TEXTBUTTON) {
				if (isClicked)
					frame = 2;
				else
					frame = 1;

			}
			else if (buttonType == ButtonType::NORMAL) {

				frame = 1;

			}
		}

		counter++;
	}
}

