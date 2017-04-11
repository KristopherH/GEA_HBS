#pragma once
#include <d3d11_1.h>
#include <string>
#include "DDSTextureLoader.h"
#include "..\DXTK_Wrapper\CustomMath.h"

class Renderer;

//=================================================================
//A Game Object 2D for displaying images
//image needs to have been converted to a dds by the Assets project
//add orginal file to this project and set it to "Image Content Pipeline"
// in a similar fashion as getting the models
//=================================================================

using namespace DirectX;
using namespace std;

class Sprite
{
public:
	Sprite(std::string _fileName, Renderer* _renderer);
	Sprite();
	virtual ~Sprite();

	ID3D11ShaderResourceView* GetTexture() { return m_pTextureRV; } //his needs to be removed
	Vec4 GetColour() { return colour; }
	Vec2 GetOrigin() { return origin; }
	Vec2 GetSize();

protected:

	Vec4 colour;
	Vec2 origin;
	ID3D11ShaderResourceView* m_pTextureRV;
};