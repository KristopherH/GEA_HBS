#pragma once
//C++
#include <memory>

//OURS
namespace Phyre
{
	namespace PRendering
	{
		class PRenderer;
	}
	namespace PSprite
	{
		class PSpriteCollection;
	}
	enum PResult;
	class PCameraPerspective;
	class PWorldMatrixOrbitController;
}

class GameObject;
class BaseCamera;
class Sprite;

class Renderer
{
public:
	Renderer(Phyre::PRendering::PRenderer* _renderer);
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

	virtual Phyre::PResult addToCollection(Phyre::PSprite::PSpriteCollection * _collection);
	virtual Phyre::PSprite::PSpriteCollection* getCollection() { return collection; };

private:
	Phyre::PSprite::PSpriteCollection* collection;
	Phyre::PRendering::PRenderer* renderer;
	Phyre::PCameraPerspective*					m_camera;								// The camera to be used for rendering the scene.
	Phyre::PWorldMatrixOrbitController*			m_cameraController;						// The camera controller used to orientate the camera within the scene.
	float										m_previousDistance;						// The previous camera distance.

};
