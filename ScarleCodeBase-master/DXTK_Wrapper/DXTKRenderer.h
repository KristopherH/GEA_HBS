#pragma once
#include <d3d11_1.h>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <memory>
class GameObjectV2;

using namespace std;
using namespace DirectX;

class Renderer
{
public:
	Renderer(ID3D11Device* _pd3dDevice, HWND _hWnd);
	~Renderer();

	bool BeginDraw();
	bool Draw(GameObjectV2* _go);
	bool EndDraw();

	ID3D11Device* GetDevice() { return pd3dDevice; }
	HWND GetWindow() { return hWnd; }

private:
	ID3D11Device* pd3dDevice;
	HWND hWnd;

	//spritebatch stuff
	unique_ptr<SpriteBatch>	spriteBatch;
	unique_ptr<SpriteFont> m_Font;
};
