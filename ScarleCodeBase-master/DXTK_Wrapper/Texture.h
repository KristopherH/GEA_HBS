#pragma once
//C++
#include <string>
#include <vector>

//DXTK
#include <d3d11_1.h>
#include "DDSTextureLoader.h"

//OURS
#include "CustomMath.h"

class Renderer;

class Texture
{
public:
	Texture(std::string _fileName, Renderer* _renderer);

	Vec2 getSize();
	void LoadPixelMap();
	bool isTransparent(Vec2 _pixel_pos, Rect box);
	bool isTransparent(Vec2 _pixel_pos);
	ID3D11ShaderResourceView* getTexture() { return m_pTextureRV; }

protected:
	ID3D11ShaderResourceView* m_pTextureRV;

	ID3D11Texture2D* captureTexture;

	std::vector<Vec4> pixelMap;
	unsigned int collision_opacity = 100;

	D3D11_TEXTURE2D_DESC description;
};