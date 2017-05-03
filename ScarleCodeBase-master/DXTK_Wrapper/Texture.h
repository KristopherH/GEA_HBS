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
	ID3D11ShaderResourceView* getTexture() { return m_pTextureRV; }

protected:
	ID3D11ShaderResourceView* m_pTextureRV;
	ID3D11Texture2D* captureTexture;

	std::vector<Vec4> pixelMap;
};