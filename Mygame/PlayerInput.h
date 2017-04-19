#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#define KEYDOWN(name, key) (name[key] & 0x80)
//#define DIK_LEFT 0x1F
#include <iostream>
#include "Constants.h"
#include <d3dx9.h>
class PlayerInput
{
public: 

	LPDIRECTINPUT8 DI_OBJECT;
	LPDIRECTINPUTDEVICE8 DI_Device;
	LPDIRECTINPUTDEVICE8 M_Device;	

	DIMOUSESTATE m_mouseState;			//MOUSESTATE IS USED FOR RECORDING THE CURRENT STATE OF KEYBOARD AND MOUSE DEVICES
	bool ReadMouse();
	void convertRelativeToAbsolute();
	int mouseX, mouseY;

	D3DXVECTOR2 GetMouseLocation();
	bool leftClickDown;
	bool rightClickDown;

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

	bool zeroKey;
	int zroKey;
	bool oneKey;
	int onKey;
	bool twoKey;
	int twKey;
	bool threeKey;
	int threKey;
	bool fourKey;
	int forKey;
	bool fiveKey;
	int fveKey;
	bool sixKey;
	int sxKey;
	bool sevenKey;
	int svenKey;
	bool eightKey;
	int eghtKey;
	bool nineKey;
	int ninKey;
	bool dotKey;
	int dtKey;

	bool keyPressed;

	HRESULT hr;
	PlayerInput();
	~PlayerInput();
	
};

#endif