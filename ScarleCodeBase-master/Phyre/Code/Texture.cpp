#include "Texture.h"
//C++

//DXTK

//OURS
#include "Renderer.h"

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

Texture::Texture(std::string _fileName, Renderer * _renderer)
{
	m_spriteCollection = _renderer->getCollection();
	m_id = 0;
}

Vec2 Texture::getSize()
{
	Phyre::PUInt32 width, height;
	m_spriteCollection->getSpriteTextureSize(m_id, width, height);
	return Vec2(width, height);
}
