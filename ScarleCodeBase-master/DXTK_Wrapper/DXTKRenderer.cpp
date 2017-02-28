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
			_go->GetScale(),
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

float Renderer::getWindowWidth()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.right - rc.left;
}

float Renderer::getWindowHeight()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc.bottom - rc.top;
}

void Renderer::DrawString(wchar_t const * text, Vec2 const & position, Vec4 const & color, float rotation, Vec2 const & origin, Vec2 const & scale, float layerDepth) const
{
	m_Font->DrawString(spriteBatch.get(), text, position, color, rotation, origin, scale, layerDepth);
}


	

//
//_Use_decl_annotations_
//inline XMVECTOR XM_CALLCONV XMLoadFloat2
//(
//	const XMFLOAT2* pSource
//	)
//{
//	assert(pSource);
//#if defined(_XM_NO_INTRINSICS_)
//	XMVECTOR V;
//	V.vector4_f32[0] = pSource->x;
//	V.vector4_f32[1] = pSource->y;
//	V.vector4_f32[2] = 0.f;
//	V.vector4_f32[3] = 0.f;
//	return V;
//#elif defined(_XM_ARM_NEON_INTRINSICS_)
//	float32x2_t x = vld1_f32(reinterpret_cast<const float*>(pSource));
//	float32x2_t zero = vdup_n_f32(0);
//	return vcombine_f32(x, zero);
//#elif defined(_XM_SSE_INTRINSICS_)
//	__m128 x = _mm_load_ss(&pSource->x);
//	__m128 y = _mm_load_ss(&pSource->y);
//	return _mm_unpacklo_ps(x, y);
//#endif
//}