#include "DXTKRenderer.h"
//C++

//DXTK
#include <CommonStates.h>

//OURS
#include "GameObject.h"
#include "BaseCamera.h"
#include "Helper.h"
#include "Sprite.h"
#include "../DXTK_Wrapper/Texture.h"

Renderer::Renderer(ID3D11Device * _pd3dDevice, HWND _hWnd)
	:pd3dDevice(_pd3dDevice), hWnd(_hWnd)
{
	////Create DirectXTK spritebatch stuff
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	spriteBatch.reset(new SpriteBatch(pd3dImmediateContext));
	spriteFont.reset(new SpriteFont(_pd3dDevice, L"../Assets/yoster.spritefont"));
	//m_DD2D->m_Font.reset(new SpriteFont(_pd3dDevice, L"..\\Assets\\italic.spritefont"));

	////set up DirectXTK Effects system
    //m_fxFactory = new EffectFactory(_pd3dDevice);

	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;
}

Renderer::~Renderer()
{
}

bool Renderer::BeginDraw(OurMatrix* transformMatrix)
{
	if (transformMatrix == nullptr)
	{
		spriteBatch->Begin();
	}
	else
	{
		DirectX::SimpleMath::Matrix transMat = OurMatrix::toDXTK(*transformMatrix);
		spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, nullptr, transMat);
	}
	return true;
}

bool Renderer::BeginDraw(BaseCamera * mainCamera)
{
	DirectX::SimpleMath::Matrix transMat = OurMatrix::toDXTK(mainCamera->GetTransMat());
	DirectX::CommonStates states(pd3dDevice);
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, states.NonPremultiplied(), nullptr, nullptr, nullptr, nullptr, transMat);
	return false;
}

bool Renderer::Draw(Sprite* _sprite)
{
	spriteBatch->Draw(_sprite->GetTexture()->getTexture(),
		_sprite->getPosition(),
		nullptr,
		/*_go->GetSprite()->GetColour()*/ DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
		_sprite->getRotation(),
		_sprite->getOrigin(),
		_sprite->getScale(),
		SpriteEffects_None);
	return true;
}

bool Renderer::Draw(Sprite * _sprite, int index)
{
	int width = _sprite->getFrameWidth();
	int height = _sprite->getFrameHeight();
	int x = _sprite->getPosition().x;
	int y = _sprite->getPosition().y;
	int sprites_across = _sprite->getSpritesAcross();

	/*Rect source = Rect(Vec2(((float)(index % _sprite->getSpritesAcross()) * width),
		(float)(index / _sprite->getSpritesAcross()) * height),
		Vec2((((float)(index % _sprite->getSpritesAcross()) * width) + width,
		(float)(index / _sprite->getSpritesAcross()) * height) + height));*/

	Rect destination = Rect(Vec2((float)x, (float)y),
							Vec2((float)(x + width), (float)(y + height)));

	if (_sprite->getSpritesAcross() > 1)
	{
		float min_x = (float)((index % 5) * width);
		float min_y = (float)((index / 5) * height);
		float max_x = (float)(((index % 5) * width) + width);
		float max_y = (float)(((index / 5) * height) + height);

		Vec2 min = Vec2(min_x, min_y);
		Vec2 max = Vec2(max_x, max_y);

		Rect source = Rect(min, max);
		RECT* src = new RECT();

		src->left = min_x;
		src->top = min_y;
		src->right = max_x;
		src->bottom = max_y;

		//_sprite->setSource(source);

		Vec2 scale = _sprite->getScale();
		
		Vec2 size = Vec2(scale.x * max.x, scale.y * max.y);

		spriteBatch->Draw(_sprite->GetTexture()->getTexture(),
						  _sprite->getPosition(),
						  src,
						  /*_go->GetSprite()->GetColour()*/ DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
						  _sprite->getRotation(),
						  _sprite->getOrigin(),
						  _sprite->getScale(),
						  SpriteEffects_None);
		return true;
	}
	else
	{
		spriteBatch->Draw(_sprite->GetTexture()->getTexture(),
							_sprite->getPosition(),
							nullptr,
							/*_go->GetSprite()->GetColour()*/ DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
							_sprite->getRotation(),
							_sprite->getOrigin(),
							_sprite->getScale(),
							SpriteEffects_None);
		return true;
	}
}

/*
	Sprite width and sprite height passed
*/

bool Renderer::EndDraw()
{
	spriteBatch->End();
	return true;
}

void Renderer::renderText(string text, Vec2 position, Vec4 colour, float rotation, Vec2 origin, float scale)
{
	// To outline text set desired colour value to 250 and other two values to 1 e.g for green outline - (1.0f, 250.0f, 1.0f)
	spriteFont->DrawString(spriteBatch.get(), Helper::charToWChar(text.c_str()), position, (DirectX::SimpleMath::Vector4)colour, rotation, origin, scale);
}

void Renderer::renderText(string text, Vec2 position, Vec4 colour, float rotation, Vec2 origin, Vec2 containingRectSize)
{
	if (spriteFont)
	{
		// calculate required rect
		SimpleMath::Vector2 size = spriteFont->MeasureString(Helper::charToWChar(text.c_str()));
		float scale = containingRectSize.x / size.x ;
		// To outline text set desired colour value to 250 and other two values to 1 e.g for green outline - (1.0f, 250.0f, 1.0f)
		Vec2 newPos = position;
		newPos += containingRectSize / 2;
		scale *= 0.8f;
		newPos.x -= ((size.x* scale) / 2);
		newPos.y -= ((size.y* scale) / 2);

		
		spriteFont->DrawString(spriteBatch.get(), Helper::charToWChar(text.c_str()), newPos, (DirectX::SimpleMath::Vector4)colour, rotation, origin, scale);
	}
}

float Renderer::getAspectRatio()
{
	//find how big my window is to correctly calculate my aspect ratio
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	return (float)width / (float)height;
}

float Renderer::getWindowWidth()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return (float)(rc.right - rc.left);
}

float Renderer::getWindowHeight()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return (float)(rc.bottom - rc.top);
}