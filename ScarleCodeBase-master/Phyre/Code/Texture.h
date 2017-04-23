#pragma once
//C++
#include <string>

//DXTK

//OURS
#include "../Code/CustomMath.h"
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
	Phyre::PSprite::PSpriteCollection* getTexture() { return m_spriteCollection; }

protected:
	Phyre::PSprite::PSpriteCollection  *m_spriteCollection; // Pointer to the sprite collection. 
	int m_id;
	//ID3D11ShaderResourceView* m_pTextureRV;
};