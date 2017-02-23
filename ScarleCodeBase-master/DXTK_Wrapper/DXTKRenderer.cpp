#include "DXTKRenderer.h"
#include "GameObjectV2.h"

Renderer::Renderer(ID3D11Device * _pd3dDevice, HWND _hWnd)
	:pd3dDevice(_pd3dDevice), hWnd(_hWnd)
{
	////Create DirectXTK spritebatch stuff
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	spriteBatch.reset(new SpriteBatch(pd3dImmediateContext));
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
	spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, nullptr, transMat);
	return false;
}

bool Renderer::Draw(GameObjectV2 * _go)
{
	if (_go->GetSprite() != nullptr)
	{
		spriteBatch->Draw(_go->GetSprite()->GetTexture(),
			_go->GetPosition(),
			nullptr,
			/*_go->GetSprite()->GetColour()*/ DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
			_go->GetRotation(),
			_go->GetSprite()->GetOrigin(),
			_go->GetSize(),
			SpriteEffects_None);
		return true;
	}
	return false;
}

bool Renderer::EndDraw()
{
	spriteBatch->End();
	return true;
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

