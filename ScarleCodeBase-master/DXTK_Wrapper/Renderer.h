#pragma once
//C++
#include <memory>

//DXTK
#include <d3d11_1.h>
#include "SimpleMath.h"

//OURS
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "../DXTK_Wrapper/CustomMath.h"

class GameObject;
class BaseCamera;
class Sprite;

using namespace std;
using namespace DirectX;

class Renderer
{
public:
	Renderer(ID3D11Device* _pd3dDevice, HWND _hWnd);
	~Renderer();

	bool BeginDraw(OurMatrix* transformMatrix = nullptr);
	bool BeginDraw(BaseCamera* mainCamera);
	//bool Draw(GameObject* _go);
	bool Draw(Sprite* _sprite);
	bool EndDraw();
	void renderText(string text, Vec2 position);

	ID3D11Device* GetDevice() { return pd3dDevice; }
	HWND GetWindow() { return hWnd; }

	float getAspectRatio();
	float getWindowWidth();
	float getWindowHeight();

	//void DrawString (wchar_t const * text, Vec2 const & position, Vec4 const & color, float rotation, Vec2 const & origin, Vec2 const & scale, float layerDepth) const;

private:
	ID3D11Device* pd3dDevice;
	HWND hWnd;
	string newText;

	//spritebatch stuff
	unique_ptr<SpriteBatch> spriteBatch;
	unique_ptr<SpriteFont> spriteFont;
};
