#pragma once
#include "..\DXTK_Wrapper\CustomMath.h"
#include "..\Main_Engine\GameObjectV2.h"

class BaseCamera : public GameObjectV2
{
public:
	BaseCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up = Vec3::Up, Vec3 _target = Vec3::Zero);
	~BaseCamera();

	virtual bool Update();

	virtual bool Draw();

	//Getters
	OurMatrix GetProj() { return m_projMat; }
	OurMatrix GetView() { return m_viewMat; }
	OurMatrix GetTransMat() { return m_worldMat; }

	//Setters

protected:
	//Principle transforms/matrices for this camera
	OurMatrix m_projMat;
	OurMatrix m_viewMat;
	OurMatrix m_worldMat;

	//parameters for setting up a camera
	float width;
	float height;
	float nearPlane;
	float farPlane;

	Vec3 m_target;
	Vec3 m_up;

	float rotation = 0.0f;
	float zoom = 1.0f;
};
