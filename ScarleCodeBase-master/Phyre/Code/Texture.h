#pragma once
//C++
#include <string>

//DXTK

//OURS
#include "CustomMath.h"
#include <Phyre.h>
#include <Rendering\PhyreRenderer.h>
#include <Sprite\PhyreSprite.h>

#include <Phyre.h>
#include <Framework/PhyreFramework.h>
#include <Rendering/PhyreRendering.h>
#include <Geometry/PhyreGeometry.h>
#include <Scene/PhyreScene.h>
#include <Serialization/PhyreSerialization.h>
#include <Sprite/PhyreSprite.h>

using namespace Phyre;
using namespace PFramework;
using namespace PRendering;
using namespace PGeometry;
using namespace PSerialization;
using namespace PInputs;
using namespace Vectormath::Aos;

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
	Phyre::PCluster m_cluster;
	//ID3D11ShaderResourceView* m_pTextureRV;
};