#include "BaseCamera.h"

BaseCamera::BaseCamera(float _width, float _height, float _nearPlane, float _farPlane, Vec3 _up, Vec3 _target)
{
	width = _width;
	height = _height;
	nearPlane = _nearPlane;
	farPlane = _farPlane;

	m_target = _target;
	m_up = _up;

	position = Vec2(10.0f, 10.0f);

	Vec3 pos3d(position.x, position.y, 1.0f);

	m_projMat = OurMatrix::CreateOrthographic(width, height, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
}

BaseCamera::~BaseCamera()
{
}

bool BaseCamera::Update()
{
	//position.x += 0.1f;
	Vec3 pos3d(position.x, position.y);

	m_projMat = OurMatrix::CreateOrthographic(width, height, nearPlane, farPlane);
	m_viewMat = OurMatrix::CreateLookAt(pos3d, m_target, m_up);

	m_worldMat = OurMatrix::CreateTrasform(pos3d, rotation, zoom, width, height);
	return false;
}

bool BaseCamera::Draw()
{
	//DO NOTHING FOR NOW
	return false;
}


