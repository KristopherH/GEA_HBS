#include "Texture.h"
//C++

//DXTK

//OURS
#include "DXTKRenderer.h"
#include "Helper.h"

Texture::Texture(std::string _fileName, Renderer * _renderer)
	:m_pTextureRV(nullptr)
{
	std::string fullfilename =
#if DEBUG
		"../Debug/"
#else
		"../Release/"
#endif
		+ _fileName + ".dds";
	HRESULT hr = CreateDDSTextureFromFile(_renderer->GetDevice(), Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);

	if (hr != S_OK)
	{
		OutputDebugString("Sprite File Not Found");
	}

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
