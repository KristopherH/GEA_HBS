#pragma once
#include "..\DXTK_Wrapper\CustomMath.h"
#include "../Game/Helper.h"
#include "../DXTK_Wrapper/DXTKRenderer.h"
#include <string>
#include <d3d11_1.h>
#include "SpriteBatch.h"

using namespace std;
using namespace DirectX;

class Text
{
public:
	Text() = default;
	~Text() = default;

	void createString(string text, Renderer* _renderer);
private:
	string newText = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	unique_ptr<SpriteBatch> spriteBatch;

};
