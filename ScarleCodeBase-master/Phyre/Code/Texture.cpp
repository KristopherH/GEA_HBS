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
	PCluster::LoadAssetFile(m_cluster, "Media/" PHYRE_PLATFORM_ID "/Samples/Sprite/sprite.phyre");

	PCluster **clustersEnd	= &m_cluster + 1;
	for (PCluster **cluster = &m_cluster; cluster < clustersEnd; cluster++)
		((*cluster)->resolveAssetReferences());
	for (PCluster **cluster = &m_cluster; cluster < clustersEnd; cluster++)
		((*cluster)->fixupInstances());

	PSharray<PAssetReference *> assetReferences;
	PChar *file;
	file = "Samples/Sprite/sprite.agx";//(Phyre::PChar*)_fileName.c_str();
	PAssetReference::Find(assetReferences, NULL, file, &PHYRE_CLASS(PTexture2D));
	PTexture2D *texture;
	//if (assetReferences.getCount() > 0)
	//{
		const PAssetReference *ar = assetReferences[0];
		const PCluster *cluster;
		cluster = ar->getCluster();
		texture = (PTexture2D*)&ar->getAsset();
	//}

	PSharray<PAssetReference *> assetReferences1;
	PChar *file1;
	file1 = "Shaders/PhyreSprite";
	PAssetReference::Find(assetReferences1, NULL, file1, &PHYRE_CLASS(PMaterial));
	PMaterial *material;
	//if (assetReferences.getCount() > 0)
	//{
		const PAssetReference *ar1 = assetReferences[0];
		const PCluster *cluster1;
		cluster1 = ar1->getCluster();
		material = (PMaterial*)&ar1->getAsset();
	//}
	
	PMesh &mesh = PSprite::s_utilitySprite.createQuadMesh();

	sprite = PHYRE_NEW PSprite::PSpriteCollection();

	// Create a sprite collection with maximum of sprites.
	// Use 2 buffers to allow CPU update while the GPU is rendering.
	sprite->initialize(*m_cluster, 1, *material, *texture, mesh, true);
	sprite->setBufferCount(2);
}

Vec2 Texture::getSize()
{
	Phyre::PUInt32 width, height;
	sprite->getSpriteTextureSize(0, width, height);
	return Vec2(width, height);
}
