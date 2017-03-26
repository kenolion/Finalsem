#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#define KEYDOWN(name, key) (name[key] & 0x80)
//#define DIK_LEFT 0x1F
#include <iostream>
#include "Constants.h"
#include "DxSound.h"

class PlayerInput
{
public: 

	LPDIRECTINPUT8 DI_OBJECT;
	LPDIRECTINPUTDEVICE8 DI_Device;
	LPDIRECTINPUTDEVICE8 M_Device;	

	//Zer add these ====================================================
	DIMOUSESTATE m_mouseState;			//MOUSESTATE IS USED FOR RECORDING THE CURRENT STATE OF KEYBOARD AND MOUSE DEVICES
	int m_mouseX, m_mouseY;
	bool ReadMouse();
	void convertRelativeToAbsolute();
	int mouseX, mouseY; //To be used to do checking.

	void GetMouseLocation(int& mouseX, int& mouseY);
	bool leftClickDown;
	//Zer add these ====================================================

	//RAWINPUTDEVICE rawinput[1];
	bool initializeKeyboard( HWND hwnd);
	bool initializeMouse(HWND hwnd);
	char keys[256];
	void getInput();
	int leftAKey;
	int rightAKey;
	int downAKey;
	int upAKey;
	int zKey;
	int tempRemapKey;

	void remapKeys();
	bool upArrowKey;
	bool downArrowKey;
	bool rightArrowKey;
	bool leftArrowKey;
	bool jumpKey;

	bool keyPressed;

	HRESULT hr;
	PlayerInput();
	~PlayerInput();
	
};

#endif