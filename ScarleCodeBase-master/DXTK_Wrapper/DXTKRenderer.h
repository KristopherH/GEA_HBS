#pragma once
#include <d3d11_1.h>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include <memory>
#include "CustomMath.h"
#include "BaseCamera.h"

class GameObjectV2;

using namespace std;
using namespace DirectX;

enum spriteeffects
{

};

class Renderer
{
public:
	Renderer(ID3D11Device* _pd3dDevice, HWND _hWnd);
	~Renderer();

	bool BeginDraw(OurMatrix* transformMatrix = nullptr);
	bool BeginDraw(BaseCamera* mainCamera);
	bool Draw(GameObjectV2* _go);
	bool EndDraw();

	ID3D11Device* GetDevice() { return pd3dDevice; }
	HWND GetWindow() { return hWnd; }

	float getAspectRatio();
	float getWindowWidth();
	float getWindowHeight();

	void DrawString (wchar_t const * text, Vec2 const & position, Vec4 const & color, float rotation, Vec2 const & origin, Vec2 const & scale, float layerDepth) const;

private:
	ID3D11Device* pd3dDevice;
	HWND hWnd;

	//spritebatch stuff
	unique_ptr<SpriteBatch>	spriteBatch;
	unique_ptr<SpriteFont> m_Font;
};
