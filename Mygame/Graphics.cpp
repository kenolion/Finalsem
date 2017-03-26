#include "Graphics.h"




bool Graphics::initialize(HWND hw, int w, int h)
{
	hwnd = hw;
	width = w;
	height = h;
	//initialize direct3d
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL) {
		::MessageBox(hwnd,
			"DirectX runtime library is not installed.",
			"System error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//Fil in some parameters
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	result = direct3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&device3d);
	if (FAILED(result)) {
		::MessageBox(hwnd,
			"Device3d failed to create",
			"System error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	result = D3DXCreateFont(device3d,			    //(1st Parameter) [LPDIRECT3DDEVICE9] Pointer to an IDirect3DDevice9 interface, the device to be associated with the font object.
		25,										//(2nd Parameter) [INT] The height of the characters in logical units.
		0,										//(3rd Parameter) [UINT] The width of the characters in logical units. 
		0,										//(4th Parameter) [UINT] Typeface weight. One example is bold.
		1,										//(5th Parameter) [UINT] The number of mipmap levels.
		false,									//(6th Parameter) [BOOL] True for italic font, false otherwise.
		DEFAULT_CHARSET, 						//(7th Parameter) [DWORD] The character set of the font.
		OUT_TT_ONLY_PRECIS,						//(8th Parameter) [DWORD] Specifies how Windows should attempt to match the desired font sizes and characteristics with actual fonts. Use OUT_TT_ONLY_PRECIS for instance, to ensure that you always get a TrueType font.
		DEFAULT_QUALITY,						//(9th Parameter) [DWORD] Specifies how Windows should match the desired font with a real font. It applies to raster fonts only and should not affect TrueType fonts
		DEFAULT_PITCH | FF_DONTCARE,			//(10th Parameter) [DWORD]Pitch and family index
		"Arial",								//(11th Parameter) [LPCSTR] String containing the typeface name. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR. See Remarks. 
		&font);									//(12th Parameter) [LPD3DXFONT]Returns a pointer to an ID3DXFont interface, representing the created font object.

	if (FAILED(result))
	{
		MessageBox(NULL, "ERROR", "Could not initialize Font", MB_ICONERROR);
		return false;
	}


	return true;

}



void Graphics::clear(D3DCOLOR color)
{
	device3d->Clear(0, NULL, D3DCLEAR_TARGET,
		color, 1.0f, 0);  // 0x00000000 = black
}

void Graphics::begin()
{
	device3d->BeginScene();
}


void Graphics::createLine()
{
	D3DXCreateLine(device3d, &line);
}

void Graphics::lineBegin()
{
	line->Begin(); 
}

void Graphics::drawLine(D3DXVECTOR2 VECTOR[] ,int noOfCoordinates, int r, int g, int b)
{
	line->Draw(VECTOR, noOfCoordinates, D3DCOLOR_XRGB(r, g, b));

}

void Graphics::end()
{
	// end scene
	device3d->EndScene();
}

void Graphics::lineEnd()
{
	line->End();
}

void Graphics::drawfont(std::string text, int number , int noOfChar, float x, float y, LPD3DXSPRITE sprite, D3DXCOLOR color, int bottom)
{
	text += std::to_string(number);
	fontRect.top = y;
	fontRect.left = x;
	fontRect.right = fontRect.left + text.length()*11;
	fontRect.bottom = fontRect.top + bottom;
	
	

	font->DrawText(sprite,
		text.c_str(),
		text.length(),				
		&fontRect,
		0,
		color);

}

void Graphics::present()
{
	device3d->Present(NULL, NULL, NULL, NULL);
}

void Graphics::cleanup()
{
	//
	// cleanup your objects here
	//

	if (device3d) {
		device3d->Release();
		device3d = NULL;
	}
	if (direct3d) {
		direct3d->Release();
		direct3d = NULL;
	}

	if (line) {	
		line->Release();
		line = NULL;
	}
	if (font) {
		font->Release();
		font = NULL;
	}
}



Graphics::Graphics()
{
	device3d = NULL;
}


Graphics::~Graphics()
{

}
