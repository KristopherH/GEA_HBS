#include "Texture.h"
//C++

//DXTK

//OURS
#include "Renderer.h"

using namespace Phyre;
using namespace PRendering;
using namespace PGeometry;

Texture::Texture(std::string _fileName, Renderer * _renderer)
{
	PSharray<PAssetReference *> assetReferences;
	PChar *file;
	file = (Phyre::PChar*)_fileName.c_str();
	PAssetReference::Find(assetReferences, NULL, file, &PHYRE_CLASS(PTexture2D));
	PTexture2D *texture;
	if (assetReferences.getCount() > 0)
	{
		const PAssetReference *ar = assetReferences[0];
		const PCluster *cluster;
		cluster = ar->getCluster();
		texture = (PTexture2D*)&ar->getAsset();
	}

	PSharray<PAssetReference *> assetReferences;
	PChar *file;
	file = "Shaders/PhyreSprite";
	PAssetReference::Find(assetReferences, NULL, file, &PHYRE_CLASS(PMaterial));
	PMaterial *material;
	if (assetReferences.getCount() > 0)
	{
		const PAssetReference *ar = assetReferences[0];
		const PCluster *cluster;
		cluster = ar->getCluster();
		material = (PMaterial*)&ar->getAsset();
	}
	
	PMesh &mesh = PSprite::s_utilitySprite.createQuadMesh();

	sprite = PHYRE_NEW PSprite::PSpriteCollection();

	// Create a sprite collection with maximum of sprites.
	// Use 2 buffers to allow CPU update while the GPU is rendering.
	sprite->initialize(m_cluster, 1, *material, *texture, mesh, true);
	sprite->setBufferCount(2);
}

Vec2 Texture::getSize()
{
	Phyre::PUInt32 width, height;
	sprite->getSpriteTextureSize(0, width, height);
	return Vec2(width, height);
}
