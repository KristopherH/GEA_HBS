#pragma once
//C++
#include <memory>

//DXTK

//OURS
#include "CustomMath.h"

#include <Phyre.h>
#include <Rendering/PhyreRendering.h>

class GameObject;
class BaseCamera;
class Sprite;

using namespace Phyre;

class Renderer
{
public:
	Renderer(PRendering::PRenderer* _renderer);
	/*ID3D11Device* _pd3dDevice, HWND _hWnd*/
	~Renderer();

	//bool BeginDraw(OurMatrix* transformMatrix = nullptr);
	bool BeginDraw(BaseCamera* mainCamera);
	bool Draw(Sprite* _sprite);
	bool EndDraw();
	//void renderText(string text, Vec2 position);

	/*ID3D11Device* GetDevice() { return pd3dDevice; }
	HWND GetWindow() { return hWnd; }*/

	float getAspectRatio();
	float getWindowWidth();
	float getWindowHeight();
	void setCameraAspect(float);

private:
	PRendering::PRenderer* renderer;
	Phyre::PCameraPerspective					m_camera;								// The camera to be used for rendering the scene.
	Phyre::PWorldMatrixOrbitController			m_cameraController;						// The camera controller used to orientate the camera within the scene.

	float										m_previousDistance;						// The previous camera distance.

};
