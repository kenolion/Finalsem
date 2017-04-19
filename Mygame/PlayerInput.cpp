#include "PlayerInput.h"



bool PlayerInput::ReadMouse()
{
	hr = M_Device->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState); //Read the Mouse Device
	if (FAILED(hr))
	{
		//If the mouse lost focus or was not acquired then try to get control back.
		if ((hr== DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			M_Device->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void PlayerInput::convertRelativeToAbsolute()
{
	
	mouseX += m_mouseState.lX; //mousestate.IX IS THE RELATIVE X POSITION 
	mouseY += m_mouseState.lY; //mousestate.IY is the RELATIVE Y position

	//Ensure the mouse location doesn't exceed the screen width or height.
	if (mouseX <= 0)
	{
		mouseX = 0;
	}
	if (mouseY <= 0)
	{
		mouseY = 0;
	}

	if (mouseX > GAME_WIDTH)
	{ 
		mouseX = GAME_WIDTH;
	}
	if (mouseY > GAME_HEIGHT)
	{
		mouseY = GAME_HEIGHT;
	}

}

D3DXVECTOR2 PlayerInput::GetMouseLocation() //Stores the mouseX and mouseY into the mouseXandmouseY in this class
{
	return D3DXVECTOR2(mouseX, mouseY);

}


bool PlayerInput::initializeKeyboard(HWND hwnd)		//Function that displays error message if play input is false
{
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DI_OBJECT, NULL);

	if (FAILED(hr)) {
		std::cout << "Failed to create Directinput object";
		system("pause");
		return false;
	}

	hr = DI_OBJECT->CreateDevice(GUID_SysKeyboard, &DI_Device, NULL);

	if (FAILED(hr)) {
		std::cout << "Failed to create directinput Device";
		system("pause");
		return false;
	}

	hr = DI_Device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		std::cout << "Failed to set data format";
		system("pause");
		return false;
	}
	hr = DI_Device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		std::cout << "Failed to set cooperative level";
		system("pause");
		return false;
	}
	
	return true;

}

bool PlayerInput::initializeMouse(HWND hwnd)
{
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DI_OBJECT, NULL);
	hr = DI_OBJECT->CreateDevice(GUID_SysMouse, &M_Device, NULL);


	if (FAILED(hr)) {
		std::cout << "Failed to create Directinput object";
		system("pause");
		return false;
	}

	hr = M_Device->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		MessageBox(NULL, "Failed to set Mouse data format.", NULL, MB_ICONERROR);
		system("pause");
		return false;
	}

	hr = M_Device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		std::cout << "Failed to set cooperative level";
		system("pause");
		return false;
	}


	return true;


}

void PlayerInput::getInput()		//Function that gets the player input
{

	HRESULT hr;
	hr = DI_Device->Acquire();
	ZeroMemory(keys, sizeof(keys));
	DI_Device->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	
	if (KEYDOWN(keys, leftAKey)) {
		leftArrowKey = true;
		keyPressed = true;
	}
	if (KEYDOWN(keys, rightAKey)) {
		rightArrowKey = true;
		keyPressed = true;
	}
	if (KEYDOWN(keys, upAKey)) {
		upArrowKey = true;
		keyPressed = true;
	}
	if (KEYDOWN(keys, downAKey)) {
		downArrowKey = true;
		keyPressed = true;

	}
	if (KEYDOWN(keys, zKey)) {
		jumpKey = true;
		keyPressed = true;
	}
	//NUMBERS ---------------------------------------------------------------------
	if (KEYDOWN(keys, zroKey)) {
		zeroKey = true;
		keyPressed = true;
	}

	if (zeroKey == true && keys[zroKey] == 0)
	{
		zeroKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, onKey)) {
		oneKey = true;
		keyPressed = true;
	}
	
	if (oneKey == true && keys[onKey] == 0)
	{
		oneKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, twKey))
	{
		twoKey = true;
		keyPressed = true;
	}

	if (twoKey == true && keys[twKey] == 0)
	{
		twoKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, threKey))
	{
		threeKey = true;
		keyPressed = true;
	}

	if (threeKey == true && keys[threKey] == 0)
	{
		threeKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, forKey))
	{
		fourKey = true;
		keyPressed = true;
	}

	if (fourKey == true && keys[forKey] == 0)
	{
		fourKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, fveKey))
	{
		fiveKey = true;
		keyPressed = true;
	}

	if (fiveKey == true && keys[fveKey] == 0)
	{
		fiveKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, sxKey))
	{
		sixKey = true;
		keyPressed = true;
	}

	if (sixKey == true && keys[sxKey] == 0)
	{
		sixKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, svenKey))
	{
		sevenKey = true;
		keyPressed = true;
	}

	if (sevenKey == true && keys[svenKey] == 0)
	{
		sevenKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, eghtKey))
	{
		eightKey = true;
		keyPressed = true;
	}

	if (eightKey == true && keys[eghtKey] == 0)
	{
		eightKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, ninKey))
	{
		nineKey = true;
		keyPressed = true;
	}

	if (nineKey == true && keys[ninKey] == 0)
	{
		nineKey = false;
		keyPressed = false;
	}

	if (KEYDOWN(keys, dtKey))
	{
		dotKey = true;
		keyPressed = true;
	}

	if (dotKey == true && keys[dtKey] == 0)
	{
		dotKey = false;
		keyPressed = false;
	}
	//-----------------------------------------------------------------------------
	if (leftArrowKey == true && keys[leftAKey] ==0) {

		leftArrowKey = false;
		keyPressed = false;
	}
	if (rightArrowKey == true && keys[rightAKey] == 0) {

		rightArrowKey = false;
		keyPressed = false;
	}
	if (downArrowKey == true && keys[downAKey] == 0) {
		downArrowKey = false;
		keyPressed = false;
	}
	if (upArrowKey == true && keys[upAKey] == 0) {
		
		upArrowKey = false;
		keyPressed = false;
	}
	if (jumpKey == true && keys[zKey] == 0) {
		jumpKey = false;
		keyPressed = false;
	}

	//MOUSE INPUT
	if (m_mouseState.rgbButtons[0])
	{
		//If LeftClickDown already true, don't go in.
		leftClickDown = true;
		//Check if time passes after 1 second, disable invincibility.
		
	}
	else
	{
		leftClickDown = false;
	}

	if	(m_mouseState.rgbButtons[1])
	{
		rightClickDown = true;
	}
	else
	{
		rightClickDown = false;
	}
	
}



PlayerInput::PlayerInput()		//Initialization of player input defailt values
{
	leftAKey = 203;
	rightAKey = 205;
	downAKey = 208;
	upAKey = 200;
	zKey = 44;
	
	zroKey = 11;
	onKey = 2;
	twKey = 3;
	threKey = 4;
	forKey = 5;
	fveKey = 6;
	sxKey = 7;
	svenKey = 8;
	eghtKey = 9;
	ninKey = 10;

	dtKey = 52;

	M_Device = 0; //Make Direct Input interface variables to null.
	m_mouseState.lX = GAME_WIDTH / 2;
	m_mouseState.lY = GAME_HEIGHT / 2;
}

//void PlayerInput::remapKeys()		
//{
//	HRESULT hr;
//
//	std::cout << "What key do you want to rebind?" << std::endl;
//
//	while (keys[59] != -1) {
//		
//		ZeroMemory(keys, sizeof(keys));
//		DI_Device->GetDeviceState(sizeof(keys), (LPVOID)&keys);
//		for (int a = 0; a < 256; a++) {
//			if (a == 59) {
//				a++;
//			}
//			if (keys[a] != 0) {
//				std::cout << a << ":" << keys[a] << std::endl;
//				tempRemapKey = a;
//				keys[59] = -1;
//			}
//
//
//
//		}
//	}
//	system("pause");
//	std::cout << "Enter another key"<<std::endl;
//	ZeroMemory(keys, sizeof(keys));
//	while (keys[59] != -1) {
//		hr = DI_Device->Acquire();
//		ZeroMemory(keys, sizeof(keys));
//		DI_Device->GetDeviceState(sizeof(keys), (LPVOID)&keys);
//		for (int a = 0; a < 256; a++) {
//			if (a == 59) {
//				a++;
//			}
//			if (keys[a] != 0) {
//				std::cout << a << ":" << keys[a] << std::endl;
//				if (tempRemapKey == leftAKey) {
//					leftAKey = a;
//				}
//				else if (tempRemapKey == rightAKey) {
//					rightAKey = a;
//				}
//				else if (tempRemapKey == upAKey) {
//					upAKey = a;
//				}
//				else if (tempRemapKey == rightAKey) {
//
//					rightAKey = a;
//				}
//
//				keys[59] = -1;
//
//			}
//
//
//
//		}
//	}
//
//}


PlayerInput::~PlayerInput()
{
	DI_Device->Unacquire();
	DI_Device->Release();
	M_Device->Unacquire();
	M_Device->Release();
}
