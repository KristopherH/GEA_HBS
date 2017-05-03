#include "Texture.h"
//C++

//DXTK

//OURS
#include "DXTKRenderer.h"
#include "Helper.h"
#include "GameData.h"

Texture::Texture(std::string _fileName, Renderer * _renderer)
	:m_pTextureRV(nullptr)
{
	std::string fullfilename =
#if DEBUG
#if ARCADE
		"../Arcade/"
#else
		"../Debug/"
#endif
#else
		"../Release/"
#endif
		+ _fileName + ".dds";

	HRESULT hr = CreateDDSTextureFromFile(_renderer->GetDevice(), Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);

	if (hr != S_OK)
	{
		OutputDebugString("Sprite File Not Found");
	}

	//CaptureImage();

	//Why don't you just call getSize in here?
	//this nasty thing is required to find out the size of this image!

	/*ID3D11Resource *pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D *)pResource)->GetDesc(&Desc);*/
}

Vec2 Texture::getSize()
{
	//this nasty thing is required to find out the size of this image!
	ID3D11Resource *pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D *)pResource)->GetDesc(&Desc);
	
	return Vec2((float)Desc.Width, (float)Desc.Height);
}

void Texture::LoadPixelMap()
{
	// Boolean value that halts the Render() method from actually executing writing calls
	//processingFrame = true;

	//captureTexture_Desc  is of type D3D11_TEXTURE2D_DESC
	ID3D11Resource *pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D *)pResource)->GetDesc(&Desc);

	ID3D11DeviceContext* pd3dImmediateContext;
	GameData::renderer->GetDevice()->GetImmediateContext(&pd3dImmediateContext);


	ID3D11Texture2D* pTexture;
	HRESULT hr = pResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&pTexture);

	assert(pTexture);

	//captureTexture_Desc  is of type D3D11_TEXTURE2D_DESC
	pTexture->GetDesc(&Desc);


	// Otherwise, create a staging texture from the non-MSAA source
	Desc.BindFlags = 0;
	Desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	Desc.Usage = D3D11_USAGE_STAGING;

	hr = GameData::renderer->GetDevice()->CreateTexture2D(&Desc, 0, &(this->captureTexture));

	assert((this->captureTexture));

	pd3dImmediateContext->CopyResource((this->captureTexture), pResource);

	//// Copy the renderTarget texture resource to my "captureTexture" resource
	//DX::ThrowIfFailed(
	//	copyRenderTarget(captureTexture.Get())
	//	);
	//HRESULT hr = copyRenderTarget(m_cameraTexture.Get());

	// Map my "captureTexture" resource to access the pixel data
	D3D11_MAPPED_SUBRESOURCE mapped;
	pd3dImmediateContext->Map((ID3D11Texture2D *)captureTexture, 0, D3D11_MAP_READ, 0, &mapped);

	// Cast the pixel data to a byte array essentially
	const uint8_t* sptr = reinterpret_cast<const uint8_t*>(mapped.pData);
	if (!sptr)
	{
		pd3dImmediateContext->Unmap(captureTexture, 0);
		return;// E_POINTER;
	}
	// Loop through all pixels in texture and copy to output buffer
	int counter = 0;
	int* outputBuffer = new int[Desc.Width * Desc.Height];
	pixelMap.resize(Desc.Width * Desc.Height);
	for (UINT row = 0; row < Desc.Height; row++)
	{
		UINT rowStart = row * mapped.RowPitch;
		for (UINT col = 0; col < Desc.Width; col++)
		{
			UINT colStart = col * 4;

			byte R = sptr[rowStart + colStart + 0]; // Red
			byte G = sptr[rowStart + colStart + 1]; // Green
			byte B = sptr[rowStart + colStart + 2];  // Blue
			byte A = sptr[rowStart + colStart + 3];  // Alpha

			int r = (int)R;
			int g = (int)G;
			int b = (int)B;
			int a = (int)A;
			
			if (a != 0)
			{
				int i = 0;
			}

			pixelMap[row * Desc.Width + col].x = r;
			pixelMap[row * Desc.Width + col].y = g;
			pixelMap[row * Desc.Width + col].z = b;
			pixelMap[row * Desc.Width + col].w = a;
			//outputBuffer[row + col] = A << 24 + R << 16 + G << 8 + B;
		}
	}
	description = Desc;
	// Unmap the texture & clean up
	pd3dImmediateContext->Unmap(captureTexture, 0);
}

bool Texture::isTransparent(Vec2 _pixel_pos, Rect box)
{
	int pos = (_pixel_pos.y * getSize().x) + _pixel_pos.x;

	if (pixelMap[pos].w <= 0)
		return true;

	return false;
}

bool Texture::isTransparent(Vec2 _pixel_pos)
{
	//int pos = (_pixel_pos.y) + _pixel_pos.x;
	//int sizey = getSize().y;
	//int sizex = getSize().x;
	//int size = getSize().x * getSize().y;

	//if (pos < 0 || pos > size)
	//	return false;

	if (pixelMap[(int)(_pixel_pos.y) * description.Width + (int)(_pixel_pos.x)].w <= collision_opacity)
		return true;

	return false;
}
