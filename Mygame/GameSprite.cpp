#include "GameSprite.h"


GameSprite::GameSprite()
{

	
}

void GameSprite::initializeTex(LPDIRECT3DDEVICE9 device3d,std::string file, int width, int height, int row, int col,D3DXCOLOR color)  
{
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device3d,				//(1st Parameter) [LPDIRECT3DDEVICE9] Pointer to an IDirect3DDevice9 interface, representing the device to be associated
		file.c_str(),													//(2nd Parameter) [LPCTSTR] Pointer to a string that specifies the filename. If the compiler settings require Unicode, the data type LPCTSTR resolves to LPCWSTR. Otherwise, the string data type resolves to LPCSTR
		width,															//(3rd Parameter) [UINT] How big your sprite sheet is in width. Width in pixels. If this value is zero or D3DX_DEFAULT, the dimensions are taken from the file and rounded up to a power of two. If the device supports non-power of 2 textures and D3DX_DEFAULT_NONPOW2 is specified, the size will not be rounded.
		height,															//(4th Parameter) [UINT] How big your sprite sheet is in height. Height, in pixels. If this value is zero or D3DX_DEFAULT, the dimensions are taken from the file and rounded up to a power of two. If the device supports non-power of 2 textures and D3DX_DEFAULT_NONPOW2 is sepcified, the size will not be rounded.
		D3DX_DEFAULT,													//(5th Parameter) [UINT] Number of mip levels requested. If this value is zero or D3DX_DEFAULT, a complete mipmap chain is created. If D3DX_FROM_FILE, the size will be taken exactly as it is in the file, and the call will fail if this violates device capabilities.
		0,																//(6th Parameter) [DWORD] 0, D3DUSAGE_RENDERTARGET, or D3DUSAGE_DYNAMIC. Setting this flag to D3DUSAGE_RENDERTARGET indicates that the surface is to be used as a render target. The resource can then be passed to the pNewRenderTarget parameter of the SetRenderTarget method. If either D3DUSAGE_RENDERTARGET or D3DUSAGE_DYNAMIC is specified, Pool must be set to D3DPOOL_DEFAULT, and the application should check that the device supports this operation by calling CheckDeviceFormat. D3DUSAGE_DYNAMIC indicates that the surface should be handled dynamically. See Using Dynamic Textures.
		D3DFMT_UNKNOWN,													//(7th Parameter) [D3DFORMAT] Member of the D3DFORMAT enumerated type, describing the requested pixel format for the texture. The returned texture might have a different format from that specified by Format. Applications should check the format of the returned texture. If D3DFMT_UNKNOWN, the format is taken from the file. If D3DFMT_FROM_FILE, the format is taken exactly as it is in the file, and the call will fail if this violates device capabilities.
		D3DPOOL_MANAGED,												//(8th Parameter) [D3DPOOL] Member of the D3DPOOL enumerated type, describing the memory class into which the texture should be placed.
		D3DX_DEFAULT, 													//(9th Parameter) [DWORD] A combination of one or more D3DX_FILTER constants controlling how the image is filtered.Specifying D3DX_DEFAULT for this parameter is the equivalent of specifying D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER.
		D3DX_DEFAULT,													//(10th Parameter) [DWORD] A combination of one or more D3DX_FILTER constants controlling how the image is filtered.Specifying D3DX_DEFAULT for this parameter is the equivalent of specifying D3DX_FILTER_BOX.In addition, use bits 27 - 31 to specify the number of mip levels to be skipped(from the top of the mipmap chain) when a.dds texture is loaded into memory; this allows you to skip up to 32 levels.
		color,															//(11th Parameter) [D3DCOLOR] D3DCOLOR value to replace with transparent black, or 0 to disable the color key. This is always a 32-bit ARGB color, independent of the source image format. Alpha is significant and should usually be set to FF for opaque color keys. Thus, for opaque black, the value would be equal to 0xFF000000.
		NULL,															//(12th Parameter) [D3DXIMAGE_INFO] Pointer to a D3DXIMAGE_INFO structure to be filled in with a description of the data in the source image file, or NULL.
		NULL,															//(13th Parameter) [PALETTEENTRY] Pointer to a PALETTEENTRY structure, representing a 256-color palette to fill in, or NULL.
		&tex)))															//(14th Parameter) [LPDIRECT3DTEXTURE9] Address of a pointer to an IDirect3DTexture9 interface, representing the created texture object.

	{
		std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL);

	}
	
	

}




void GameSprite::draw( LPD3DXSPRITE sprite, RECT spriteRect,D3DCOLOR color)
{


	if (tex == NULL) {
		MessageBox(NULL, "tex is empty", "", MB_OK);

	}

	if (sprite == NULL) {
		MessageBox(NULL, "sprite is empty", "", MB_OK);

	}

	if (sprite && tex) {
		
		sprite->Draw(tex, &spriteRect, NULL,NULL, color);
		

	}
}


GameSprite::~GameSprite()
{
	if (tex) {
		tex->Release();
		tex = 0;
	}
	
}

