#pragma once
//C++
#include <memory>

//DXTK
#include <d3d11_1.h>
#include "SimpleMath.h"

//OURS
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "CustomMath.h"

class GameObject;
class BaseCamera;
class Sprite;

using namespace std;
using namespace DirectX;

class Renderer
{
	friend class Texture;
public:
	Renderer(ID3D11Device* _pd3dDevice, HWND _hWnd);
	~Renderer();

	bool BeginDraw(OurMatrix* transformMatrix = nullptr);
	bool BeginDraw(BaseCamera* mainCamera);
	//bool Draw(GameObject* _go);
	bool Draw(Sprite* _sprite); 
	bool Draw(GameObject* _sprite);
	bool EndDraw();
	//void renderText(string text, Vec2 position);
	void renderText(string text, Vec2 position, Vec4 colour, float rotation, Vec2 origin, float scale);
	void renderText(string text, Vec2 position, Vec4 colour, float rotation, Vec2 origin, Vec2 containingRectSize);

	ID3D11Device* GetDevice() { return pd3dDevice; }
	HWND GetWindow() { return hWnd; }

	float getAspectRatio();
	float getWindowWidth();
	float getWindowHeight();

	Vec2 WorldToScreen(Vec2);
	Vec2 ScreenToWorld(Vec2);
private:
	ID3D11Device* pd3dDevice;
	HWND hWnd;
	string newText;

	//spritebatch stuff
	unique_ptr<SpriteBatch> spriteBatch;
	unique_ptr<SpriteFont> spriteFont;
};
