
//C++

//Phyre

//OURS
#include <../Main_Engine/GameObject.h>
#include <../Main_Engine/BaseCamera.h>

#include <Rendering\PhyreRenderInterface.h>

#include "Texture.h"
#include "Renderer.h"
#include "CustomMath.h"

using namespace PRendering;

Renderer::Renderer(PRendering::PRenderer* _renderer)
{
	renderer = _renderer;
}

Renderer::~Renderer()
{
}

bool Renderer::BeginDraw(BaseCamera* mainCamera)
{
	PHYRE_TRY(m_cameraController.bind(m_camera));
	m_cameraController.setDistance(35.0f);
	m_cameraController.setFromMatrix(OurMatrix::toPHYRE(mainCamera->GetProj()));

	// Tell the renderer which camera we want to use for rendering
	renderer->setCamera(m_camera);
	PHYRE_TRY(renderer->setClearColor(0.1f, 0.1f, 0.8f, 0.5f));
	PHYRE_TRY(renderer->beginScene(PRenderInterfaceBase::PE_CLEAR_COLOR_BUFFER_BIT | PRenderInterfaceBase::PE_CLEAR_DEPTH_BUFFER_BIT));

	return false;
}

bool Renderer::Draw(Sprite* _sprite)
{
	//spriteBatch->Draw(_sprite->GetTexture()->getTexture(),
	//	_sprite->getPosition(),
	//	nullptr,
	//	/*_go->GetSprite()->GetColour()*/ DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
	//	_sprite->getRotation(),
	//	_sprite->getOrigin(),
	//	_sprite->getScale(),
	//	SpriteEffects_None);
	
	if (_sprite->GetTexture()->getTexture() && _sprite->GetTexture()->getTexture()->m_quadMeshInstance)
		renderer->renderMeshInstance(*_sprite->GetTexture()->getTexture()->m_quadMeshInstance);

	// Iterate through all mesh instances in the cluster and render them for the Opaque render pass
	renderer->setSceneRenderPassType(PHYRE_GET_SCENE_RENDER_PASS_TYPE(Opaque));
	//renderWorld(m_world, m_camera);
	// Render the text objects
	/*for (PUInt32 i = 0; i < c_totalTextStrings; i++)
	{
		if (m_text[i])
			PHYRE_TRY(m_text[i]->renderText(m_renderer));
	}*/


	return true;
}

bool Renderer::EndDraw()
{
	PHYRE_TRY(renderer->endScene());
	return true;
}

void Renderer::setCameraAspect(float ratio)
{
	m_camera.setAspect(ratio);
	m_camera.updateViewMatrices();
}