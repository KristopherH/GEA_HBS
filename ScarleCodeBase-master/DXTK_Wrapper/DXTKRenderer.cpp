#include "DXTKRenderer.h"
//C++

//DXTK
#include <CommonStates.h>

//OURS
#include "GameObject.h"
#include "BaseCamera.h"
#include "Helper.h"
#include "../DXTK_Wrapper/Texture.h"
#include "../DXTK_Wrapper/Sprite.h"

Renderer::Renderer(ID3D11Device * _pd3dDevice, HWND _hWnd)
	:pd3dDevice(_pd3dDevice), hWnd(_hWnd)
{
	////Create DirectXTK spritebatch stuff
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	spriteBatch.reset(new SpriteBatch(pd3dImmediateContext));
	spriteFont.reset(new SpriteFont(_pd3dDevice, L"../Assets/italic.spritefont"));
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

bool Renderer::EndDraw()
{
	spriteBatch->End();
	return true;
}

void Renderer::renderText(string text, Vec2 position)
{
	spriteFont->DrawString(spriteBatch.get(), Helper::charToWChar(text.c_str()), position);
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

//void Renderer::DrawString(wchar_t const * text, Vec2 const & position, Vec4 const & color, float rotation, Vec2 const & origin, Vec2 const & scale, float layerDepth) const
//{
//	m_Font->DrawString(spriteBatch.get(), text, position, color, rotation, origin, scale, layerDepth);
//}