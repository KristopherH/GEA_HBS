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
	ID3D11ShaderResourceView* getTexture() { return m_pTextureRV; }

protected:
	ID3D11ShaderResourceView* m_pTextureRV;

};