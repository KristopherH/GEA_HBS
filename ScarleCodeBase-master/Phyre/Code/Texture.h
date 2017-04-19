#pragma once
//C++
#include <string>

//DXTK

//OURS
#include "CustomMath.h"
namespace Phyre
{
	namespace  PSprite
	{
		class PSpriteCollection;
	}
	class PCluster;
}
class Renderer;

class Texture
{
public:
	Texture(std::string _fileName, Renderer* _renderer);

	Vec2 getSize();

	
	//ID3D11ShaderResourceView* getTexture() { return m_pTextureRV; }
	Phyre::PSprite::PSpriteCollection* getTexture() { return sprite; }

protected:
	Phyre::PSprite::PSpriteCollection* sprite;
	Phyre::PCluster* m_cluster;
	//ID3D11ShaderResourceView* m_pTextureRV;
};