#include "Sprite.h"
#include "../Game/Helper.h"
#include "../DXTK_Wrapper/DXTKRenderer.h"

Sprite::Sprite(std::string _fileName, Renderer* _renderer) 
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

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource *pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D *)pResource)->GetDesc(&Desc);
	
	origin = Vec2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done
	origin *= 0.5f;
}

Sprite::~Sprite()
{
}
